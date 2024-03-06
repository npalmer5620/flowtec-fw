// SDSU Team FlowTec 2024
// Side note: What the heck is ARM/ST doing this was so difficult to configure: https://community.st.com/t5/stm32cubeide-mcus/stmcubeide-1-6-1-and-arm-cmsis-5-7-0-dsp/td-p/211938
#include <stdio.h>
#include <arm_math.h>

#include "main.h"

#define DISPLAY_ADDR 0x50
#define ADC_BUF_LEN 4096
#define SAMPLE_RATE 4096
#define FILTER_TAP_NUM 181 // Number of filter coefficients

// Define the FIR filter coefficient array (for a rectangular filter, all values might be the same)
const float32_t firCoeffs[FILTER_TAP_NUM] = {0.000023443031574970, -0.000007622163525896, 0.000024472710301737, -0.000015794529336838, 0.000023744351746176, -0.000023916211879136, 0.000021296594202570, -0.000031299106709746, 0.000017293291246228, -0.000037208993588648, 0.000012008844372858, -0.000040913852924948, 0.000005804661368727, -0.000041736177732350, -0.000000901232129657, -0.000039105555390336, -0.000007668820614303, -0.000032607562492557, -0.000014072003631067, -0.000022025091964018, -0.000019732715708973, -0.000007368619840171, -0.000024350365177795, 0.000011107400780900, -0.000027724112752286, 0.000032903904228292, -0.000029766142872210, 0.000057293113880618, -0.000030504872978020, 0.000083350555807508, -0.000030077928970222, 0.000110001551689631, -0.000028715611707926, 0.000136079442237573, -0.000026716410899524, 0.000160391857795117, -0.000024416816067176, 0.000181790676699123, -0.000022158168459649, 0.000199240951681896, -0.000020253549334838, 0.000211884073073870, -0.000018957686783836, 0.000219090780284846, -0.000018442586388948, -0.009591306601852246, 0.000069482579859417, -0.009475861160777591, 0.003497667368075381, -0.008563360996068185, 0.007147723867630799, -0.006915976018906973, 0.010724004687226184, -0.004658854737535398, 0.013893811850062009, -0.001970757629105354, 0.016309211965631662, 0.000929986567316979, 0.017631814214382945, 0.003803080660830224, 0.017558736253384027, 0.006405975035698917, 0.015847796291925551, 0.008514060828994478, 0.012339935752909727, 0.009939640333238145, 0.006977004130177236, 0.010548058910278831, -0.000186679465403701, 0.010269606192472934, -0.008980153539286469, 0.009106139171838449, -0.019119668938778499, 0.007131817309817127, -0.030220616328723946, 0.004487833143241908, -0.041816957926465906, 0.001371529009781722, -0.053387009971141153, -0.001979232020066168, -0.064383913633848350, -0.005305166328349748, -0.074268741673010730, -0.008346565956360063, -0.082543949174321687, -0.010864447782730546, -0.088784810372820724, -0.012660092108511148, -0.092666597254738456, -0.013591336314476970, 0.909779997810787444, -0.013591336314476891, -0.092666597254738636, -0.012660092108511220, -0.088784810372820655, -0.010864447782730487, -0.082543949174321507, -0.008346565956360111, -0.074268741673010508, -0.005305166328349722, -0.064383913633848461, -0.001979232020066183, -0.053387009971141250, 0.001371529009781717, -0.041816957926465795, 0.004487833143241931, -0.030220616328723918, 0.007131817309817080, -0.019119668938778502, 0.009106139171838489, -0.008980153539286483, 0.010269606192472861, -0.000186679465403718, 0.010548058910278879, 0.006977004130177242, 0.009939640333238079, 0.012339935752909738, 0.008514060828994512, 0.015847796291925502, 0.006405975035698870, 0.017558736253383965, 0.003803080660830248, 0.017631814214382938, 0.000929986567316974, 0.016309211965631662, -0.001970757629105363, 0.013893811850061990, -0.004658854737535358, 0.010724004687226127, -0.006915976018906991, 0.007147723867630813, -0.008563360996068104, 0.003497667368075379, -0.009475861160777619, 0.000069482579859390, -0.009591306601852156, -0.000018442586388955, 0.000219090780284844, -0.000018957686783786, 0.000211884073073866, -0.000020253549334835, 0.000199240951681886, -0.000022158168459671, 0.000181790676699116, -0.000024416816067191, 0.000160391857795110, -0.000026716410899503, 0.000136079442237577, -0.000028715611707922, 0.000110001551689632, -0.000030077928970239, 0.000083350555807508, -0.000030504872978030, 0.000057293113880615, -0.000029766142872162, 0.000032903904228296, -0.000027724112752274, 0.000011107400780903, -0.000024350365177815, -0.000007368619840172, -0.000019732715708976, -0.000022025091964014, -0.000014072003631046, -0.000032607562492562, -0.000007668820614298, -0.000039105555390331, -0.000000901232129660, -0.000041736177732351, 0.000005804661368726, -0.000040913852924943, 0.000012008844372862, -0.000037208993588652, 0.000017293291246229, -0.000031299106709738, 0.000021296594202556, -0.000023916211879137, 0.000023744351746166, -0.000015794529336835, 0.000024472710301779, -0.000007622163525894, 0.000023443031574975 };

// Define FIR state
static float32_t firState[ADC_BUF_LEN + FILTER_TAP_NUM - 1]; // taps + block_size - 1
arm_fir_instance_f32 firInstance;

// Peripherals
I2C_HandleTypeDef hi2c1;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;

// Global Variables
// static volatile uint16_t adc_buf[ADC_BUF_LEN];
static volatile uint16_t head = 0;
static volatile float32_t data[ADC_BUF_LEN];
float32_t output[ADC_BUF_LEN];
float32_t corrs[ADC_BUF_LEN * 2 - 1];
float32_t period;
uint8_t i2c_buffer[64];
uint8_t digits[16];
uint8_t count;
uint8_t deccount;
int decimalPlaces;
char msg[64];

// Prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);

// Helper Functions : TODO MOVE
#include <math.h> // Ensure this is included for fabs() and other math functions

float distance_between_maxima_average(float array[], int size) {
    int i, maxima_index = -1;
    float last_maxima;
    float total_distance = 0;
    int maxima_count = 0;

    // Loop through the array to find local maxima
    for (i = 1; i < size - 1; i++) {
        if (array[i] > array[i - 1] && array[i] > array[i + 1]) {
            if (maxima_index != -1) {
                // Calculate distance from the last maxima
                total_distance += (i - maxima_index);
                maxima_count++; // Increment count of maxima distances
            }

            // Update last maxima details
            last_maxima = array[i];
            maxima_index = i;
        }
    }

    // If no maxima found or only one maxima found, return -1
    if (maxima_count == 0) {
        return -1;
    }

    // Calculate average distance
    float average_distance = total_distance / maxima_count;

    // Optional: Output the result via UART or any other mechanism
    // sprintf(msg, "Average Distance: %f\r\n", average_distance);
    // HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), 5);

    return average_distance;
}

void display_init(void) {
    // Display On
    i2c_buffer[0] = 0xFE; // Prefix
    i2c_buffer[1] = 0x41; // Display On
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 2, HAL_MAX_DELAY);
    HAL_Delay(100);

    //sprintf(usart_buffer, "Display Started\r\n");
    //HAL_UART_Transmit(&huart2, (uint8_t*)usart_buffer, strlen(usart_buffer), HAL_MAX_DELAY);

    // Clear display
    i2c_buffer[1] = 0x51; // Clear screen
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 2, 1000);
    HAL_Delay(100);

    //sprintf(usart_buffer, "Display Cleared\r\n");
    //HAL_UART_Transmit(&huart2, (uint8_t*)usart_buffer, strlen(usart_buffer), HAL_MAX_DELAY);

    // Set contrast
    i2c_buffer[1] = 0x52;
    i2c_buffer[2] = 40; // contrast 1 - 50

    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 3, 1000);
    HAL_Delay(100);

    // Set Backlight Level
    i2c_buffer[1] = 0x53;
    i2c_buffer[2] = 4; // backlight 1 - 8
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 3, 1000);
    HAL_Delay(100);

    i2c_buffer[1] = 0x48; // underline cursor off
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 2, 1000);
    HAL_Delay(100);

    i2c_buffer[1] = 0x70; // underline cursor off
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 2, 1000);
    HAL_Delay(2000);
}

void extractDigits(float32_t period, uint8_t digits[], uint8_t * count) {
    char numStr[50]; // Assuming a maximum of 50 characters in the string representation
    sprintf(numStr, "%.4f", period);

    int len = strlen(numStr);
    int totalDigits = 0;

    // Extract digits from the string
    for (int i = 0; i < len; ++i) {
        if (numStr[i] == '.') {
            digits[totalDigits++] = -1; // Placeholder for the decimal point
        } else {
            digits[totalDigits++] = numStr[i] - '0';
        }
    }

    // Update the number of digits in the array
    * count = totalDigits;
}

void display_result() {
    extractDigits(period, digits, & count);

    i2c_buffer[0] = 0xFE; //clear display
    i2c_buffer[1] = 0x51;
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 2, 1000);
    HAL_Delay(100);

    for (int i = 0; i < count; i++) {
        if (digits[i] == 255) {
            i2c_buffer[0] = '.';
        } else {
            i2c_buffer[0] = '0' + digits[i];
        }
        HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 1, 1000);
        HAL_Delay(2);
    }
    i2c_buffer[0] = 'm';
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 1, 1000);
    HAL_Delay(2);
    i2c_buffer[0] = 's';
    HAL_I2C_Master_Transmit( & hi2c1, DISPLAY_ADDR, i2c_buffer, 1, 1000);
    HAL_Delay(2);
}

int main(void) {
    // Initializers
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM3_Init();
    MX_I2C1_Init();

    // Initialize FIR
    arm_fir_init_f32( & firInstance, FILTER_TAP_NUM, firCoeffs, firState, ADC_BUF_LEN);

    // ADC DMA start
    // HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buf, ADC_BUF_LEN);

    // Start interrupt RQ
    if (HAL_ADC_Start_IT( & hadc1) != HAL_OK)
        Error_Handler();

    // Infinite Loop
    HAL_Delay(5000);

    while (1) {
        // Start timer
        HAL_TIM_PWM_Start( & htim3, TIM_CHANNEL_1);

        // Wait 1.1s
        HAL_Delay(1100);

        sprintf(msg, "adc\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), HAL_MAX_DELAY);
        for (int i = 0; i < ADC_BUF_LEN; i++) {
            sprintf(msg, "%f\r\n", data[i]);
            HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), HAL_MAX_DELAY);
        }
        sprintf(msg, "end\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), HAL_MAX_DELAY);

        // FIR Filter data
        arm_fir_f32( & firInstance, (float32_t * ) data, output, ADC_BUF_LEN);

        sprintf(msg, "fir\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);
        for (int i = 0; i < ADC_BUF_LEN; i++) {
            sprintf(msg, "%f\r\n", data[i]);
            HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);
        }
        sprintf(msg, "end\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);

        // Autocorrelate float values : TODO enable optimization
        arm_correlate_f32(output, ADC_BUF_LEN, output, ADC_BUF_LEN, corrs);

        sprintf(msg, "corr\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);
        for (int i = 0; i < (ADC_BUF_LEN * 2 - 1); i++) {
            sprintf(msg, "%f\r\n", corrs[i]);
            HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);
        }
        sprintf(msg, "end\r\n");
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);

        // Compute period of 2 most relevant peaks
        period = distance_between_maxima_average(corrs, 2 * ADC_BUF_LEN - 1) * (1.0 / SAMPLE_RATE) * 1000.0;

        sprintf(msg, "%f\r\n", period);
        HAL_UART_Transmit( & huart2, (uint8_t * ) msg, strlen(msg), 5);
        display_result();
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {
        0
    };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {
        0
    };

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 70;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig( & RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig( & RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {
        0
    };

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
    hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE; // TODO HERE
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init( & hadc1) != HAL_OK) {
        Error_Handler();
    }

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
     */
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    if (HAL_ADC_ConfigChannel( & hadc1, & sConfig) != HAL_OK) {
        Error_Handler();
    }

    // Turn on ADC Global Interrupts
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
}

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 40000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init( & hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_TIM3_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {
        0
    };
    TIM_MasterConfigTypeDef sMasterConfig = {
        0
    };
    TIM_OC_InitTypeDef sConfigOC = {
        0
    };

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 8545; // 8545 = 4096 Hz
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init( & htim3) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource( & htim3, & sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init( & htim3) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization( & htim3, & sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel( & htim3, & sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init( & huart2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */
}

static void MX_DMA_Init(void) {

    /* DMA controller clock enable */
    // __HAL_RCC_DMA2_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA2_Stream0_IRQn interrupt configuration */

    //    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    //    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {
        0
    };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, & GPIO_InitStruct);

    /*Configure GPIO pin : LD2_Pin */
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, & GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef * hadc) {
    // HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * hadc) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    if (hadc == & hadc1) { // Check if the callback is from ADC1
        data[head] = ((float32_t) HAL_ADC_GetValue(hadc) / 4096.0);

        if (head == (ADC_BUF_LEN - 1)) {
            HAL_TIM_PWM_Stop( & htim3, TIM_CHANNEL_1);
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
            head = 0;
        } else head++;
    }
}

void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {}
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t * file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}

#endif
