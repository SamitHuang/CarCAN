/** @page TIM2_OC_InactiveMode Generate 3 different signals with 3 different delays with Inactive Mode

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM2/TIM2_OC_InactiveMode/readme.txt
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Description of the TIM2 Output compare Inactive mode Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim
   
  @par Example description

  This example shows how to configure the TIM peripheral to generate 3 different 
  signals with 3 different delays.

  The TIM2CLK frequency is set to 2 MHz, the Prescaler is set to 2048 and used in 
  Output Compare Inactive Mode.
 
  TIM2 counter clock = TIM2CLK / (Prescaler) = 976 Hz 


  The TIM2 CCR1 register value is equal to 976:
  TIM2_CH1 delay = CCR1_Val/TIM2 counter clock  = 1000 ms
  so the TIM2 Channel 1 generates a signal with a delay equal to 1000 ms.

  The TIM2 CCR2 register value is equal to 488:
  TIM2_CH2 delay = CCR2_Val/TIM2 counter clock = 500 ms
  so the TIM2 Channel 2 generates a signal with a delay equal to 500 ms.

  The TIM2 CCR3 register value is equal to 244:
  TIM2_CH3 delay = CCR3_Val/TIM2 counter clock = 250 ms
  so the TIM2 Channel 3 generates a signal with a delay equal to 250 ms.


  @par Directory contents

  - TIM2\TIM2_OC_InactiveMode\main.c                    Main file containing the "main" function
  - TIM2\TIM2_OC_InactiveMode\stm8s_conf.h              Library Configuration file
  - TIM2\TIM2_OC_InactiveMode\stm8s_it.c                Interrupt routines source 
  - TIM2\TIM2_OC_InactiveMode\stm8s_it.h                Interrupt routines declaration
  

  @par Hardware and Software environment

  - This example runs on STM8S and STM8A High density, Medium density devices and
    STM8S103x Low density devices.
    
  
  - This example has been tested with STMicroelectronics STM8/128-EVAL evaluation 
    board and can be easily tailored to any other development board.

  - STM8/128-EVAL Set-up
    - Connect the following pins to an oscilloscope:
	    - Pin PG.5
	    - Pin PG.6
	    - Pin PG.7

  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Connect PG.5 , PG.6 and PG.7 pins to an oscilloscope 
  
  @note
  - High-Density STM8A devices are the STM8AF52xx STM8AF6269/8x/Ax,
    STM8AF51xx, and STM8AF6169/7x/8x/9x/Ax microcontrollers where the Flash memory
    density ranges between 32 to 128 Kbytes
  - Medium-Density STM8A devices are the STM8AF622x/4x, STM8AF6266/68,
    STM8AF612x/4x, and STM8AF6166/68 microcontrollers where the Flash memory 
    density ranges between 8 to 32 Kbytes
  - High-Density STM8S devices are the STM8S207xx, STM8S007 and STM8S208xx microcontrollers
    where the Flash memory density ranges between 32 to 128 Kbytes.
  - Medium-Density STM8S devices are the STM8S105x and STM8S005 microcontrollers
    where the Flash memory density ranges between 16 to 32-Kbytes.
  - Low-Density STM8S devices are the STM8S103xx, STM8S003 and STM8S903xx microcontrollers
    where the Flash density is 8 Kbytes.
      
 * <h3><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h3>
 */
