/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef HEADER_MUTUAL_H_
#define HEADER_MUTUAL_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdint.h>
#include <stdbool.h>


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Control byte */
#define	STARTING					0xFF
#define	ENDING						0xFE

/* ID of device */
#define	ID_MST						0
#define	ID_SLV_01					1
#define	ID_SLV_02					2
#define	ID_SLV_03					3

/* Data of Slv01 */
typedef enum
{
	eSlv01SendToMst_Btn1			= '1',
	eSlv01SendToMst_Btn2			= '2',
	eSlv01SendToMst_Btn3			= '3',
	eSlv01SendToMst_Btn4			= '4',
	eSlv01SendToMst_Btn5			= '5',
	eSlv01SendToMst_Btn6			= '6',
	eSlv01SendToMst_Btn7			= '7',
	eSlv01SendToMst_Btn8			= '8',
	eSlv01SendToMst_Btn9			= '9',
} data_Of_Slv_01;


/**************************************************************************************************
 *	END OF HEADER_MUTUAL.h
 *************************************************************************************************/
#endif /* HEADER_MUTUAL_H_ */
