/*
 * bq76952.c
 *
 *  Created on: Mar 9, 2025
 *      Author: bu
 */


#include "main.h"
#include "stdint.h"
#include "stdio.h"
#include "BQ76952.h"



#define DEV_ADDR  0x10			    // BQ769x2 address is 0x10 including R/W bit or 0x8 as 7-bit address
#define CRC_Mode 0  		    	// 0 for disabled, 1 for enabled
#define MAX_BUFFER_SIZE 10
#define R 0						    // Read; Used in DirectCommands and Subcommands functions
#define W 1 				    	// Write; Used in DirectCommands and Subcommands functions
#define W2 2 				     	// Write data with two bytes; Used in Subcommands function


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c1;
extern CRC_HandleTypeDef hcrc;

/* --------------------------------- BQ76952 VARIABLES START --------------------------------- */

uint8_t RX_data [2] = {0x00, 0x00}; // farklı fonksiyonların datalarını tutmak için buffer BQ769x2

uint8_t RX_32Byte [32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	//used in Subcommands read function
// Global Variables for cell voltages, temperatures, Stack voltage, PACK Pin voltage, LD Pin voltage, CC2 current


extern uint16_t CellVoltage [16];

extern float Temperature [4];				//(+-+-+) Tasarımda 4 cell temperature mevcut TS1 TS3 HDQ CFETOFF
extern uint16_t Stack_Voltage;
extern uint16_t Pack_Voltage;
extern uint16_t LD_Voltage;
extern int16_t Pack_Current;

extern uint16_t AlarmBits;
extern uint8_t value_SafetyStatusA;  						// Safety Status Register A
extern uint8_t value_SafetyStatusB;  						// Safety Status Register B
extern uint8_t value_SafetyStatusC;  						// Safety Status Register C
extern uint8_t value_PFStatusA;   							// Permanent Fail Status Register A
extern uint8_t value_PFStatusB;  							// Permanent Fail Status Register B
extern uint8_t value_PFStatusC;   							// Permanent Fail Status Register C
extern uint8_t FET_Status;  								// FET Status register contents  - Shows states of FETs
extern uint16_t CB_ActiveCells;  							// Cell Balancing Active Cells



extern uint8_t	UV_Fault;   								   	 // under-voltage fault state
extern uint8_t	OV_Fault;  										 // over-voltage fault state
extern uint8_t	SCD_Fault;									     // short-circuit fault state
extern uint8_t	OCD_Fault;  									 // over-current fault state
extern uint8_t ProtectionsTriggered;                            // Set to 1 if any protection triggers

extern uint8_t LD_ON;					                         // Load Detect status bit
extern uint8_t DSG;  					                         // discharge FET state
extern uint8_t CHG;  					                         // charge FET state
extern uint8_t PCHG; 					                         // pre-charge FET state
extern uint8_t PDSG; 					                         // pre-discharge FET state
extern uint8_t DDSG_Pin_Status; 								//(+-+-+) FET STATUS registerı
extern uint8_t DCHG_Pin_Status;									//(+-+-+) FET STATUS registerı
extern uint8_t ALERT_Pin_Status;								//(+-+-+) FET STATUS registerı

extern uint32_t AccumulatedCharge_Int; 							// in BQ769x2_READPASSQ func
extern uint32_t AccumulatedCharge_Frac;							// in BQ769x2_READPASSQ func
extern uint32_t AccumulatedCharge_Time;							// in BQ769x2_READPASSQ func

/* --------------------------------- BQ76952 VARIABLES END --------------------------------- */

/* --------------------------------- BQ76952 APP VARIABLES START --------------------------------- */






/* --------------------------------- BQ76952 FUNCTIONS START --------------------------------- */

void delayUS(uint32_t us) {   						// mikrosaniyelik delay oluşturma fonksiyonu
	__HAL_TIM_SET_COUNTER(&htim1,0);  				// counter değerini 0 ayarla
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  	// kullanıcının girdiği değere kadar beklet
}


void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count)
{
    uint8_t copyIndex = 0;
    for (copyIndex = 0; copyIndex < count; copyIndex++)
    {
        dest[copyIndex] = source[copyIndex];
    }
}


unsigned char Checksum(unsigned char *ptr, unsigned char len)
// Calculates the checksum when writing to a RAM register. The checksum is the inverse of the sum of the bytes.
//Çalışma Mantığı
//Bu checksum, toplamın tersine alınmış hâlidir. Bu yöntem, özellikle iletişimde hata tespiti için kullanılır. Örneğin:
//Bir cihaz, gönderdiği verinin sonuna bu checksum değerini ekler.
//Alıcı cihaz, veriyi alırken aynı checksum fonksiyonunu uygular ve hesaplanan checksum ile gönderilen checksum'ı karşılaştırır.
//Eğer iki checksum eşleşirse, veri doğru iletilmiştir. Eşleşmezse, veri hatalıdır.
{
	unsigned char i;
	unsigned char checksum = 0;

	for(i=0; i<len; i++)
		checksum += ptr[i];

	checksum = 0xff & ~checksum;

	return(checksum);
}


unsigned char CRC8(unsigned char *ptr, unsigned char len)
//Calculates CRC8 for passed bytes. Used in i2c read and write functions
{
	unsigned char i;
	unsigned char crc=0;
	while(len--!=0)
	{
		for(i=0x80; i!=0; i/=2)
		{
			if((crc & 0x80) != 0)
			{
				crc *= 2;
				crc ^= 0x107;
			}
			else
				crc *= 2;

			if((*ptr & i)!=0)
				crc ^= 0x107;
		}
		ptr++;
	}
	return(crc);
}

void I2C_WriteReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count)
{
	uint8_t TX_Buffer [MAX_BUFFER_SIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
#if CRC_Mode
	{
		uint8_t crc_count = 0;
		crc_count = count * 2;
		uint8_t crc1stByteBuffer [3] = {0x10, reg_addr, reg_data[0]};
		unsigned int j;
		unsigned int i;
		uint8_t temp_crc_buffer [3];

		TX_Buffer[0] = reg_data[0];
		TX_Buffer[1] = CRC8(crc1stByteBuffer,3);

		j = 2;
		for(i=1; i<count; i++)
		{
			TX_Buffer[j] = reg_data[i];
			j = j + 1;
			temp_crc_buffer[0] = reg_data[i];
			TX_Buffer[j] = CRC8(temp_crc_buffer,1);
			j = j + 1;
		}
		HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, reg_addr, 1, TX_Buffer, crc_count, 1000);
	}
#else
	HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, reg_addr, 1, reg_data, count, 1000);
#endif
}


int I2C_ReadReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count)
{
	unsigned int RX_CRC_Fail = 0;  // reset to 0. If in CRC Mode and CRC fails, this will be incremented.
	uint8_t RX_Buffer [MAX_BUFFER_SIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
#if CRC_Mode
	{
		uint8_t crc_count = 0;
		uint8_t ReceiveBuffer [10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		crc_count = count * 2;
		unsigned int j;
		unsigned int i;
		unsigned char CRCc = 0;
		uint8_t temp_crc_buffer [3];

		HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, reg_addr, 1, ReceiveBuffer, crc_count, 1000);
		uint8_t crc1stByteBuffer [4] = {0x10, reg_addr, 0x11, ReceiveBuffer[0]};
		CRCc = CRC8(crc1stByteBuffer,4);
		if (CRCc != ReceiveBuffer[1])
		{
			RX_CRC_Fail += 1;
		}
		RX_Buffer[0] = ReceiveBuffer[0];

		j = 2;
		for (i=1; i<count; i++)
		{
			RX_Buffer[i] = ReceiveBuffer[j];
			temp_crc_buffer[0] = ReceiveBuffer[j];
			j = j + 1;
			CRCc = CRC8(temp_crc_buffer,1);
			if (CRCc != ReceiveBuffer[j])
				RX_CRC_Fail += 1;
			j = j + 1;
		}
		CopyArray(RX_Buffer, reg_data, crc_count);
	}
#else
	HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, reg_addr, 1, reg_data, count, 1000);
#endif
	return 0;
}


void BQ769x2_SetRegister(uint16_t reg_addr, uint32_t reg_data, uint8_t datalen)
{
	uint8_t TX_Buffer[2] = {0x00, 0x00};
	uint8_t TX_RegData[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	//TX_RegData in little endian format
	TX_RegData[0] = reg_addr & 0xff;
	TX_RegData[1] = (reg_addr >> 8) & 0xff;
	TX_RegData[2] = reg_data & 0xff; //1st byte of data

	switch(datalen)
    {
		case 1: //1 byte datalength
      		I2C_WriteReg(0x3E, TX_RegData, 3);
			delayUS(2000);
			TX_Buffer[0] = Checksum(TX_RegData, 3);
			TX_Buffer[1] = 0x05; //combined length of register address and data
      		I2C_WriteReg(0x60, TX_Buffer, 2); // Write the checksum and length
			delayUS(2000);
			break;
		case 2: //2 byte datalength
			TX_RegData[3] = (reg_data >> 8) & 0xff;
			I2C_WriteReg(0x3E, TX_RegData, 4);
			delayUS(2000);
			TX_Buffer[0] = Checksum(TX_RegData, 4);
			TX_Buffer[1] = 0x06; //combined length of register address and data
      		I2C_WriteReg(0x60, TX_Buffer, 2); // Write the checksum and length
			delayUS(2000);
			break;
		case 4: //4 byte datalength, Only used for CCGain and Capacity Gain
			TX_RegData[3] = (reg_data >> 8) & 0xff;
			TX_RegData[4] = (reg_data >> 16) & 0xff;
			TX_RegData[5] = (reg_data >> 24) & 0xff;
			I2C_WriteReg(0x3E, TX_RegData, 6);
			delayUS(2000);
			TX_Buffer[0] = Checksum(TX_RegData, 6);
			TX_Buffer[1] = 0x08; //combined length of register address and data
      		I2C_WriteReg(0x60, TX_Buffer, 2); // Write the checksum and length
			delayUS(2000);
			break;
    }
}


void CommandSubcommands(uint16_t command) //For Command only Subcommands
// See the TRM or the BQ76952 header file for a full list of Command-only subcommands
{	//For DEEPSLEEP/SHUTDOWN subcommand you will need to call this function twice consecutively

	uint8_t TX_Reg[2] = {0x00, 0x00};

	//TX_Reg in little endian format
	TX_Reg[0] = command & 0xff;
	TX_Reg[1] = (command >> 8) & 0xff;

	I2C_WriteReg(0x3E,TX_Reg,2);
	delayUS(2000);
}


void Subcommands(uint16_t command, uint16_t data, uint8_t type)
// See the TRM or the BQ76952 header file for a full list of Subcommands
{
	//security keys and Manu_data writes dont work with this function (reading these commands works)
	//max readback size is 32 bytes i.e. DASTATUS, CUV/COV snapshot
	uint8_t TX_Reg[4] = {0x00, 0x00, 0x00, 0x00};
	uint8_t TX_Buffer[2] = {0x00, 0x00};

	//TX_Reg in little endian format
	TX_Reg[0] = command & 0xff;
	TX_Reg[1] = (command >> 8) & 0xff;

	if (type == R) {//read
		I2C_WriteReg(0x3E,TX_Reg,2);
		delayUS(2000);
		I2C_ReadReg(0x40, RX_32Byte, 32); //RX_32Byte is a global variable
	}
	else if (type == W) {
		//FET_Control, REG12_Control
		TX_Reg[2] = data & 0xff;
		I2C_WriteReg(0x3E,TX_Reg,3);
		delayUS(1000);
		TX_Buffer[0] = Checksum(TX_Reg, 3);
		TX_Buffer[1] = 0x05; //combined length of registers address and data
		I2C_WriteReg(0x60, TX_Buffer, 2);
		delayUS(1000);
	}
	else if (type == W2){ //write data with 2 bytes
		//CB_Active_Cells, CB_SET_LVL
		TX_Reg[2] = data & 0xff;
		TX_Reg[3] = (data >> 8) & 0xff;
		I2C_WriteReg(0x3E,TX_Reg,4);
		delayUS(1000);
		TX_Buffer[0] = Checksum(TX_Reg, 4);
		TX_Buffer[1] = 0x06; //combined length of registers address and data
		I2C_WriteReg(0x60, TX_Buffer, 2);
		delayUS(1000);
	}
}


void DirectCommands(uint8_t command, uint16_t data, uint8_t type)
// See the TRM or the BQ76952 header file for a full list of Direct Commands
{	//type: R = read, W = write
	uint8_t TX_data[2] = {0x00, 0x00};

	//little endian format
	TX_data[0] = data & 0xff;
	TX_data[1] = (data >> 8) & 0xff;

	if (type == R) {//Read
		I2C_ReadReg(command, RX_data, 2); //RX_data is a global variable
		delayUS(2000);
	}
	if (type == W) {//write
    //Control_status, alarm_status, alarm_enable all 2 bytes long
		I2C_WriteReg(command,TX_data,2);
		delayUS(2000);
	}
}


void BQ769x2_Init() {




	CommandSubcommands(SET_CFGUPDATE);



	BQ769x2_SetRegister(PowerConfig, 0x2D80, 2);


	BQ769x2_SetRegister(REG0Config, 0x00, 1);							//reg0 disable

	//Enable REG1 with 3.3V output
	BQ769x2_SetRegister(REG12Config, 0x0D, 1);

	// Set DFETOFF pin to control BOTH
	BQ769x2_SetRegister(DFETOFFPinConfig, 0x42, 1);


	// This configures the ALERT pin to drive high (REG1 voltage) when enabled.
	// The ALERT pin can be used as an interrupt
	BQ769x2_SetRegister(ALERTPinConfig, 0x2A, 1);

	//(+-+-+) Tasarımda DCHG Kullanımı

	BQ769x2_SetRegister(DCHGPinConfig, 0x2A, 1);

	//(+-+-+) Tasarımda DDSG Kullanımı
	//(REG1)
	BQ769x2_SetRegister(DDSGPinConfig, 0x2A, 1);

	//Cell Temp
	BQ769x2_SetRegister(TS1Config, 0x07, 1);

	//cell Temp
	BQ769x2_SetRegister(TS3Config, 0x07, 1);

	//Cell Temp
	BQ769x2_SetRegister(HDQPinConfig, 0x07, 1);

	//cell Temp
	BQ769x2_SetRegister(CFETOFFPinConfig, 0x07, 1);




	// VCell ModeEnable 16 cells 0x0000 sets the default of 16 cells
	BQ769x2_SetRegister(VCellMode, 0x0000, 2);

	// Enable protections voltage and current
	BQ769x2_SetRegister(EnabledProtectionsA, 0xBC, 1);

	//temp protections
	BQ769x2_SetRegister(EnabledProtectionsB, 0x77, 1);						//(+-+-+) Tasarımda bq'ya bağlı fet termistör yok OTF fet temp iptal edildi. 0


	//Default Alarm Mask aktifleştirme the FullScan and ADScan bit
	BQ769x2_SetRegister(DefaultAlarmMask, 0xF886, 2);						//(+-+-+) 2.bit CB alarm tetiklemesi de etkinleştirildi

	// Automated balancing while in Relax or Charge modes
	BQ769x2_SetRegister(BalancingConfiguration, 0x03, 1);					//--------1


	BQ769x2_SetRegister(CUVThreshold, 0x32, 1);								//CUV 2530mV seçildi


	// COV (4301 mV)
	BQ769x2_SetRegister(COVThreshold, 0x55, 1);



	BQ769x2_SetRegister(OCCThreshold, 0x02, 1);								//(+-+-+)  min and default 4a


	BQ769x2_SetRegister(OCD1Threshold, 0x04, 1);							//8A max discharge overcurrent akımı seçildi


	BQ769x2_SetRegister(SCDThreshold, 0x01, 1);								//(+-+-+) 1 = 20mV = 20A SCD selection

	//0x03 (30 us) Enabled with a delay of (value - 1) * 15 µs; min value of 1
	BQ769x2_SetRegister(SCDDelay, 0x03, 1);

	// Set up SCDL Latch Limit to 1 sadece yük çıkarılınca aktifleşme durumu
	// latch kullanılmazsa normalde kendi kendine koşul değişimi kontrolü
	BQ769x2_SetRegister(SCDLLatchLimit, 0x01, 1);

	// Exit CONFIGUPDATE mode  - Subcommand 0x0092
	CommandSubcommands(EXIT_CFGUPDATE);




}

//  ********************************* FET Control Commands  ***************************************

void BQ769x2_BOTHOFF () {
	// Disables all FETs using the DFETOFF (BOTHOFF) pin

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);  //(+-+-+) DFETOFF pin (BOTHOFF) set high
}

void BQ769x2_RESET_BOTHOFF () {
	// Resets DFETOFF (BOTHOFF) pin

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);  //(+-+-+) DFETOFF pin (BOTHOFF) set low
}

void BQ769x2_ReadFETStatus() {

				//FET STATUS REG CHG PCHG DSG PDSG fet durumları ve DCHG DDSG ALERT Pin durumları
	DirectCommands(FETStatus, 0x00, R);
	FET_Status = (RX_data[1]*256 + RX_data[0]);
    DSG = ((0x4 & RX_data[0])>>2);			// discharge FET state
  	CHG = (0x1 & RX_data[0]);			// charge FET state
  	PCHG = ((0x2 & RX_data[0])>>1);		// pre-charge FET state
  	PDSG = ((0x8 & RX_data[0])>>3);		// pre-discharge FET state
	DCHG_Pin_Status = ((0x10 & RX_data[0])>>4); 	//DCHG pin state		//(+-+-+)
  	DDSG_Pin_Status = ((0x20 & RX_data[0])>>5);		//DDSG pin state		//(+-+-+)			/
  	ALERT_Pin_Status = ((0x40 & RX_data[0])>>6);	//ALERT pin state		//(+-+-+)


}

// ********************************* End of FET Control Commands *********************************

// ********************************* BQ769x2 Power Commands   *****************************************

void BQ769x2_ShutdownPin() {
	// SHUTDOWN mode RST_SHUT pin

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);  //(+-+-+) Sets RST_SHUT pin
}

void BQ769x2_ReleaseShutdownPin() {
	// Releases the RST_SHUT pin

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);  //(+-+-+) Resets RST_SHUT pin
}

// ********************************* End of BQ769x2 Power Commands   *****************************************


// ********************************* BQ769x2 Status and Fault Commands   *****************************************

uint16_t BQ769x2_ReadAlarmStatus() {
	// Read this register to find out why the ALERT pin was asserted
	DirectCommands(AlarmStatus, 0x00, R);
	return (RX_data[1]*256 + RX_data[0]);
}

void BQ769x2_ReadSafetyStatus() {
	// Read Safety Status A/B/C bits
	// This shows which primary protections have been triggered
	DirectCommands(SafetyStatusA, 0x00, R);
	value_SafetyStatusA = (RX_data[1]*256 + RX_data[0]);
	//Example Fault Flags
	UV_Fault = ((0x4 & RX_data[0])>>2);
	OV_Fault = ((0x8 & RX_data[0])>>3);
	SCD_Fault = ((0x8 & RX_data[1])>>3);
	OCD_Fault = ((0x2 & RX_data[1])>>1);

	DirectCommands(SafetyStatusB, 0x00, R);
	value_SafetyStatusB = (RX_data[1]*256 + RX_data[0]);
	DirectCommands(SafetyStatusC, 0x00, R);
	value_SafetyStatusC = (RX_data[1]*256 + RX_data[0]);
	if ((value_SafetyStatusA + value_SafetyStatusB + value_SafetyStatusC) > 1) {
		ProtectionsTriggered = 1; }
	else {
		ProtectionsTriggered = 0; }
}

void BQ769x2_ReadPFStatus() {
	// Read Permanent Fail Status A/B/C and find which bits are set
	// This shows which permanent fail triggered
	DirectCommands(PFStatusA, 0x00, R);
	value_PFStatusA = (RX_data[1]*256 + RX_data[0]);
	DirectCommands(PFStatusB, 0x00, R);
	value_PFStatusB = (RX_data[1]*256 + RX_data[0]);
	DirectCommands(PFStatusC, 0x00, R);
	value_PFStatusC = (RX_data[1]*256 + RX_data[0]);
}

// ********************************* End of BQ769x2 Status and Fault Commands   *****************************************


// ********************************* BQ769x2 Measurement Commands   *****************************************


uint16_t BQ769x2_ReadVoltage(uint8_t command)
//read a specific cell voltage or stack / pack / LD voltage
{
	//RX_data is global var

	DirectCommands(command, 0x00, R);
	if(command >= Cell1Voltage && command <= Cell16Voltage) {//Cells 1 through 16 (0x14 to 0x32)
		return (RX_data[1]*256 + RX_data[0]);    //voltage is reported in mV
	}
	else {//stack, Pack, LD
		return 10 * (RX_data[1]*256 + RX_data[0]); //voltage is reported in 0.01V units
	}

}
void BQ769x2_ReadAllVoltages()
// Reads all cell voltages, Stack voltage, PACK pin voltage, and LD pin voltage
{
  int cellvoltageholder = Cell1Voltage;       //Cell1Voltage is 0x14
  for (int x = 0; x < 16; x++){               //Reads all cell voltages
    CellVoltage[x] = BQ769x2_ReadVoltage(cellvoltageholder);
    cellvoltageholder = cellvoltageholder + 2;						//cell1base adresini holdera atayıp adresi 2 byte artır 16 bit data
  }
  Stack_Voltage = BQ769x2_ReadVoltage(StackVoltage);
  Pack_Voltage = BQ769x2_ReadVoltage(PACKPinVoltage);
  LD_Voltage = BQ769x2_ReadVoltage(LDPinVoltage);
}

uint16_t BQ769x2_ReadCurrent()
// Reads PACK current
{
	DirectCommands(CC2Current, 0x00, R);
	return (RX_data[1]*256 + RX_data[0]);  // current is reported in mA
}

float BQ769x2_ReadTemperature(uint8_t command)
{
	DirectCommands(command, 0x00, R);
	//RX_data is a global var
	return (0.1 * (float)(RX_data[1]*256 + RX_data[0])) - 273.15;  // converts from 0.1K to Celcius
}

void BQ769x2_ReadPassQ(){ // Read Accumulated Charge and Time from DASTATUS6
	Subcommands(DASTATUS6, 0x00, R);
	AccumulatedCharge_Int = ((RX_32Byte[3]<<24) + (RX_32Byte[2]<<16) + (RX_32Byte[1]<<8) + RX_32Byte[0]); //Bytes 0-3
	AccumulatedCharge_Frac = ((RX_32Byte[7]<<24) + (RX_32Byte[6]<<16) + (RX_32Byte[5]<<8) + RX_32Byte[4]); //Bytes 4-7
	AccumulatedCharge_Time = ((RX_32Byte[11]<<24) + (RX_32Byte[10]<<16) + (RX_32Byte[9]<<8) + RX_32Byte[8]); //Bytes 8-11
}


int find_max_difference(uint16_t voltages[], int size) {
    int max_value = voltages[0];
    int min_value = voltages[0];

    //maksimum fark
    for (int i = 1; i < size; i++) {
        if (voltages[i] > max_value) {
            max_value = voltages[i];
        }
        if (voltages[i] < min_value) {
            min_value = voltages[i];
        }
    }

    // En büyük farkı hesapla
    return max_value - min_value;

}



/* --------------------------------- BQ76952 FUNCTIONS END --------------------------------- */

