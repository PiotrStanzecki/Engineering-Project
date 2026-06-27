/*
 * =============================================================================
 * STM32H750xB GPIO ALTERNATE FUNCTIONS — GROUPED BY PERIPHERAL
 * Source: DS12556 Rev 7, Tables 8–18 (Port A–K Alternate Functions)
 * =============================================================================
 *
 * -----------------------------------------------------------------------
 * SYS / DEBUG (AF0)
 * -----------------------------------------------------------------------
 * PA13 : JTMS / SWDIO
 * PA14 : JTCK / SWCLK
 * PA15 : JTDI
 * PB3  : JTDO / TRACESWO
 * PB4  : NJTRST
 * PA8  : MCO1
 * PC9  : MCO2
 *
 * -----------------------------------------------------------------------
 * TIMERS
 * -----------------------------------------------------------------------
 * -- TIM1 (AF1) --
 * PA6  : TIM1_BKIN
 * PA7  : TIM1_CH1N
 * PA8  : TIM1_CH1
 * PA9  : TIM1_CH2
 * PA10 : TIM1_CH3
 * PA11 : TIM1_CH4
 * PA12 : TIM1_ETR
 * PB0  : TIM1_CH2N
 * PB1  : TIM1_CH3N
 * PB12 : TIM1_BKIN
 * PB13 : TIM1_CH1N
 * PB14 : TIM1_CH2N
 * PB15 : TIM1_CH3N
 * PE7  : TIM1_ETR
 * PE8  : TIM1_CH1N
 * PE9  : TIM1_CH1
 * PE10 : TIM1_CH2N
 * PE11 : TIM1_CH2
 * PE12 : TIM1_CH3N
 * PE13 : TIM1_CH3
 * PE14 : TIM1_CH4
 * PE15 : TIM1_BKIN
 *
 * -- TIM2 (AF1) --
 * PA0  : TIM2_CH1 / TIM2_ETR
 * PA1  : TIM2_CH2
 * PA2  : TIM2_CH3
 * PA3  : TIM2_CH4
 * PA5  : TIM2_CH1 / TIM2_ETR
 * PA15 : TIM2_CH1 / TIM2_ETR
 * PB3  : TIM2_CH2
 * PB10 : TIM2_CH3
 * PB11 : TIM2_CH4
 *
 * -- TIM3 (AF2) --
 * PA6  : TIM3_CH1
 * PA7  : TIM3_CH2
 * PB0  : TIM3_CH3
 * PB1  : TIM3_CH4
 * PB4  : TIM3_CH1
 * PB5  : TIM3_CH2
 * PC6  : TIM3_CH1
 * PC7  : TIM3_CH2
 * PC8  : TIM3_CH3
 * PC9  : TIM3_CH4
 * PD2  : TIM3_ETR
 * PE2  : TIM3_ETR
 *
 * -- TIM4 (AF2) --
 * PB6  : TIM4_CH1
 * PB7  : TIM4_CH2
 * PB8  : TIM4_CH3
 * PB9  : TIM4_CH4
 * PD12 : TIM4_CH1
 * PD13 : TIM4_CH2
 * PD14 : TIM4_CH3
 * PD15 : TIM4_CH4
 * PE0  : TIM4_ETR
 *
 * -- TIM5 (AF2) --
 * PA0  : TIM5_CH1
 * PA1  : TIM5_CH2
 * PA2  : TIM5_CH3
 * PA3  : TIM5_CH4
 * PH10 : TIM5_CH1
 * PH11 : TIM5_CH2
 * PH12 : TIM5_CH3
 * PI0  : TIM5_CH4
 *
 * -- TIM8 (AF3) --
 * PA0  : TIM8_ETR
 * PA5  : TIM8_CH1N
 * PA6  : TIM8_BKIN
 * PA7  : TIM8_CH1N
 * PB0  : TIM8_CH2N
 * PB1  : TIM8_CH3N
 * PB14 : TIM8_CH2N
 * PB15 : TIM8_CH3N
 * PC6  : TIM8_CH1
 * PC7  : TIM8_CH2
 * PC8  : TIM8_CH3
 * PC9  : TIM8_CH4
 * PI2  : TIM8_CH4
 * PI3  : TIM8_ETR
 * PI5  : TIM8_CH1
 * PI6  : TIM8_CH2
 * PI7  : TIM8_CH3
 *
 * -- TIM12 (AF2) --
 * PB14 : TIM12_CH1
 * PB15 : TIM12_CH2
 * PH6  : TIM12_CH1
 * PH9  : TIM12_CH2
 *
 * -- TIM13 (AF9) --
 * PA6  : TIM13_CH1
 * PF8  : TIM13_CH1
 *
 * -- TIM14 (AF9) --
 * PA7  : TIM14_CH1
 * PF9  : TIM14_CH1
 *
 * -- TIM15 (AF4) --
 * PA1  : TIM15_CH1N
 * PA2  : TIM15_CH1
 * PA3  : TIM15_CH2
 * PA9  : TIM15_BKIN
 * PE4  : TIM15_BKIN
 * PE5  : TIM15_CH1
 * PE6  : TIM15_CH2
 *
 * -- TIM16 (AF1) --
 * PB4  : TIM16_BKIN
 * PB6  : TIM16_CH1N
 * PB8  : TIM16_CH1
 * PF6  : TIM16_CH1
 * PF8  : TIM16_CH1N (not all packages)
 *
 * -- TIM17 (AF1) --
 * PB5  : TIM17_BKIN
 * PB7  : TIM17_CH1N
 * PB9  : TIM17_CH1
 * PF7  : TIM17_CH1
 * PF9  : TIM17_CH1N (not all packages)
 *
 * -- LPTIM1 (AF1) --
 * PB5  : LPTIM1_IN1
 * PB6  : LPTIM1_ETR
 * PB7  : LPTIM1_IN2
 * PB8  : LPTIM1_OUT
 * PG4  : LPTIM1_IN1 (AF1 on H7)
 * PG5  : LPTIM1_IN2
 * PG8  : LPTIM1_OUT
 *
 * -----------------------------------------------------------------------
 * I2C (AF4)
 * -----------------------------------------------------------------------
 * -- I2C1 --
 * PB5  : I2C1_SMBA
 * PB6  : I2C1_SCL
 * PB7  : I2C1_SDA
 * PB8  : I2C1_SCL
 * PB9  : I2C1_SDA
 *
 * -- I2C2 --
 * PB10 : I2C2_SCL
 * PB11 : I2C2_SDA
 * PB12 : I2C2_SMBA
 * PF0  : I2C2_SDA
 * PF1  : I2C2_SCL
 * PH4  : I2C2_SCL
 * PH5  : I2C2_SDA
 *
 * -- I2C3 --
 * PA8  : I2C3_SCL
 * PC9  : I2C3_SDA
 * PH7  : I2C3_SCL
 * PH8  : I2C3_SDA
 *
 * -- I2C4 (AF6) --
 * PB6  : I2C4_SCL
 * PB7  : I2C4_SDA
 * PB8  : I2C4_SCL
 * PB9  : I2C4_SDA
 * PD12 : I2C4_SCL
 * PD13 : I2C4_SDA
 * PF14 : I2C4_SCL
 * PF15 : I2C4_SDA
 * PH11 : I2C4_SCL
 * PH12 : I2C4_SDA
 *
 * -----------------------------------------------------------------------
 * SPI (AF5)
 * -----------------------------------------------------------------------
 * -- SPI1 --
 * PA4  : SPI1_NSS
 * PA5  : SPI1_SCK
 * PA6  : SPI1_MISO
 * PA7  : SPI1_MOSI
 * PA15 : SPI1_NSS
 * PB3  : SPI1_SCK
 * PB4  : SPI1_MISO
 * PB5  : SPI1_MOSI
 * PG9  : SPI1_MISO
 * PG10 : SPI1_NSS
 * PG11 : SPI1_SCK
 *
 * -- SPI2 (AF5) --
 * PA9  : SPI2_SCK
 * PA11 : SPI2_NSS
 * PA12 : SPI2_SCK
 * PB4  : SPI2_NSS
 * PB9  : SPI2_NSS
 * PB10 : SPI2_SCK
 * PB12 : SPI2_NSS
 * PB13 : SPI2_SCK
 * PB14 : SPI2_MISO
 * PB15 : SPI2_MOSI
 * PC1  : SPI2_MOSI
 * PC2  : SPI2_MISO
 * PC3  : SPI2_MOSI
 * PD3  : SPI2_SCK
 * PI0  : SPI2_NSS
 * PI1  : SPI2_SCK
 * PI2  : SPI2_MISO
 * PI3  : SPI2_MOSI
 *
 * -- SPI3 (AF6) --
 * PA4  : SPI3_NSS
 * PA15 : SPI3_NSS
 * PB2  : SPI3_MOSI
 * PB3  : SPI3_SCK
 * PB4  : SPI3_MISO
 * PB5  : SPI3_MOSI
 * PC10 : SPI3_SCK
 * PC11 : SPI3_MISO
 * PC12 : SPI3_MOSI
 *
 * -- SPI4 (AF5) --
 * PE2  : SPI4_SCK
 * PE4  : SPI4_NSS
 * PE5  : SPI4_MISO
 * PE6  : SPI4_MOSI
 * PE11 : SPI4_NSS
 * PE12 : SPI4_SCK
 * PE13 : SPI4_MISO
 * PE14 : SPI4_MOSI
 *
 * -- SPI5 (AF5) --
 * PF6  : SPI5_NSS
 * PF7  : SPI5_SCK
 * PF8  : SPI5_MISO
 * PF9  : SPI5_MOSI
 * PF11 : SPI5_NSS (AF5)
 * PH5  : SPI5_NSS
 * PH6  : SPI5_SCK
 * PH7  : SPI5_MISO
 *
 * -- SPI6 (AF8) --
 * PA5  : SPI6_SCK
 * PA6  : SPI6_MISO
 * PA7  : SPI6_MOSI
 * PB3  : SPI6_SCK
 * PB4  : SPI6_MISO
 * PB5  : SPI6_MOSI
 * PG12 : SPI6_MISO
 * PG13 : SPI6_SCK
 * PG14 : SPI6_MOSI
 *
 * -----------------------------------------------------------------------
 * USART / UART (AF7 and AF8)
 * -----------------------------------------------------------------------
 * -- USART1 (AF7) --
 * PA8  : USART1_CK
 * PA9  : USART1_TX
 * PA10 : USART1_RX
 * PA11 : USART1_CTS
 * PA12 : USART1_RTS
 * PB3  : USART1_RTS (AF7)
 * PB6  : USART1_TX
 * PB7  : USART1_RX
 * PB14 : USART1_TX (AF4 on some packages)
 * PB15 : USART1_RX (AF4 on some packages)
 *
 * -- USART2 (AF7) --
 * PA0  : USART2_CTS
 * PA1  : USART2_RTS
 * PA2  : USART2_TX
 * PA3  : USART2_RX
 * PA4  : USART2_CK
 * PD3  : USART2_CTS
 * PD4  : USART2_RTS
 * PD5  : USART2_TX
 * PD6  : USART2_RX
 * PD7  : USART2_CK
 *
 * -- USART3 (AF7) --
 * PB10 : USART3_TX
 * PB11 : USART3_RX
 * PB12 : USART3_CK
 * PB13 : USART3_CTS
 * PB14 : USART3_RTS
 * PC10 : USART3_TX
 * PC11 : USART3_RX
 * PC12 : USART3_CK
 * PD8  : USART3_TX
 * PD9  : USART3_RX
 * PD10 : USART3_CK
 * PD11 : USART3_CTS
 * PD12 : USART3_RTS
 *
 * -- UART4 (AF8) --
 * PA0  : UART4_TX
 * PA1  : UART4_RX
 * PA11 : UART4_RX  (AF6)
 * PA12 : UART4_TX  (AF6)
 * PB8  : UART4_RX
 * PB9  : UART4_TX
 * PC10 : UART4_TX
 * PC11 : UART4_RX
 * PD0  : UART4_RX
 * PD1  : UART4_TX
 * PH13 : UART4_TX
 * PH14 : UART4_RX
 * PI9  : UART4_RX
 *
 * -- UART5 (AF8) --
 * PB5  : UART5_RX
 * PB6  : UART5_TX
 * PB12 : UART5_RX
 * PB13 : UART5_TX
 * PC12 : UART5_TX
 * PD2  : UART5_RX
 *
 * -- USART6 (AF7) --
 * PC6  : USART6_TX
 * PC7  : USART6_RX
 * PC8  : USART6_CK
 * PG7  : USART6_CK
 * PG8  : USART6_RTS
 * PG9  : USART6_RX
 * PG12 : USART6_RTS
 * PG13 : USART6_CTS
 * PG14 : USART6_TX
 * PG15 : USART6_CTS
 *
 * -- UART7 (AF7) --
 * PA8  : UART7_RX  (AF11)
 * PB3  : UART7_TX
 * PB4  : UART7_RX
 * PE7  : UART7_RX
 * PE8  : UART7_TX
 * PF6  : UART7_RX
 * PF7  : UART7_TX
 *
 * -- UART8 (AF8) --
 * PE0  : UART8_RX
 * PE1  : UART8_TX
 * PJ8  : UART8_RX  (LQFP176/TFBGA packages)
 * PJ9  : UART8_TX
 *
 * -- LPUART1 (AF3) --
 * PA9  : LPUART1_TX
 * PA10 : LPUART1_RX
 * PB10 : LPUART1_TX
 * PB11 : LPUART1_RX
 *
 * -----------------------------------------------------------------------
 * SAI — Serial Audio Interface (AF6 / AF8 / AF10)
 * -----------------------------------------------------------------------
 * -- SAI1 (AF6) --
 * PA3  : SAI1_D1
 * PB0  : SAI1_SD_B
 * PB1  : SAI1_MCLK_B
 * PB2  : SAI1_SD_A  (AF6)
 * PB3  : SAI1_SCK_A (AF6)
 * PB5  : SAI1_SD_A  (AF6)
 * PB6  : SAI1_FS_B  (AF6)
 * PC1  : SAI1_SD_A  (AF6)
 * PD6  : SAI1_SD_A  (AF6)
 * PE2  : SAI1_MCLK_A
 * PE3  : SAI1_SD_B
 * PE4  : SAI1_FS_A
 * PE5  : SAI1_SCK_A
 * PE6  : SAI1_SD_A
 * PG7  : SAI1_MCLK_A
 *
 * -- SAI2 (AF8 / AF10) --
 * PA0  : SAI2_SD_B  (AF10)
 * PA2  : SAI2_SCK_B (AF8)
 * PC0  : SAI2_FS_B  (AF8)
 * PD11 : SAI2_SD_A  (AF10)
 * PD12 : SAI2_FS_A  (AF10)
 * PD13 : SAI2_SCK_A (AF10)
 * PE0  : SAI2_MCLK_A (AF10)
 * PG9  : SAI2_FS_B  (AF10)
 * PG10 : SAI2_SD_B  (AF10)
 *
 * -- SAI3 (AF6) --
 * PD4  : SAI3_SD_A  (AF6)
 * PD5  : SAI3_FS_A  (AF6)
 * PD6  : SAI3_SCK_A (AF6)
 *
 * -- SAI4 (AF8 / AF9) --
 * PC1  : SAI4_SD_A  (AF8)
 * PD11 : SAI4_SD_A  (AF8)
 * PE2  : SAI4_MCLK_A (AF9)
 * PE3  : SAI4_SD_B  (AF9)
 * PE4  : SAI4_FS_A  (AF9)
 * PE5  : SAI4_SCK_A (AF9)
 * PE6  : SAI4_SD_A  (AF9)
 *
 * -----------------------------------------------------------------------
 * I2S (AF5 / AF6 — shares pins with SPI2/SPI3)
 * -----------------------------------------------------------------------
 * PB9  : I2S2_WS
 * PB10 : I2S2_CK
 * PB12 : I2S2_WS
 * PB13 : I2S2_CK
 * PB14 : I2S2_SDI
 * PB15 : I2S2_SDO
 * PC6  : I2S2_MCK
 * PA4  : I2S3_WS   (AF6)
 * PA15 : I2S3_WS   (AF6)
 * PB3  : I2S3_CK   (AF6)
 * PB4  : I2S3_SDI  (AF6)
 * PB5  : I2S3_SDO  (AF6)
 * PC7  : I2S3_MCK  (AF6)
 * PC10 : I2S3_CK   (AF6)
 * PC11 : I2S3_SDI  (AF6)
 * PC12 : I2S3_SDO  (AF6)
 *
 * -----------------------------------------------------------------------
 * SPDIFRX (AF8)
 * -----------------------------------------------------------------------
 * PD7  : SPDIFRX_IN0
 * PD8  : SPDIFRX_IN1
 * PG11 : SPDIFRX_IN0
 * PG12 : SPDIFRX_IN1
 *
 * -----------------------------------------------------------------------
 * SDMMC (AF12)
 * -----------------------------------------------------------------------
 * -- SDMMC1 --
 * PC6  : SDMMC1_D6
 * PC7  : SDMMC1_D7
 * PC8  : SDMMC1_D0
 * PC9  : SDMMC1_D1
 * PC10 : SDMMC1_D2
 * PC11 : SDMMC1_D3
 * PC12 : SDMMC1_CK
 * PD2  : SDMMC1_CMD
 * PB8  : SDMMC1_D4
 * PB9  : SDMMC1_D5
 *
 * -- SDMMC2 (AF11) --
 * PA0  : SDMMC2_CMD
 * PB3  : SDMMC2_D2
 * PB4  : SDMMC2_D3
 * PB14 : SDMMC2_D0
 * PB15 : SDMMC2_D1
 * PD6  : SDMMC2_CK
 * PD7  : SDMMC2_CMD
 * PG9  : SDMMC2_D4 (AF11)
 *
 * -----------------------------------------------------------------------
 * FDCAN (AF9)
 * -----------------------------------------------------------------------
 * -- FDCAN1 --
 * PA11 : FDCAN1_RX
 * PA12 : FDCAN1_TX
 * PB8  : FDCAN1_RX
 * PB9  : FDCAN1_TX
 * PD0  : FDCAN1_RX
 * PD1  : FDCAN1_TX
 * PH13 : FDCAN1_TX
 * PH14 : FDCAN1_RX
 *
 * -- FDCAN2 --
 * PB5  : FDCAN2_RX
 * PB6  : FDCAN2_TX
 * PB12 : FDCAN2_RX
 * PB13 : FDCAN2_TX
 *
 * -----------------------------------------------------------------------
 * USB OTG (AF10)
 * -----------------------------------------------------------------------
 * -- USB OTG FS (USB2) --
 * PA11 : USB2_OTG_FS_DM
 * PA12 : USB2_OTG_FS_DP
 *
 * -- USB OTG HS (USB1 — internal PHY) --
 * PA9  : USB1_OTG_HS_VBUS
 * PA10 : USB1_OTG_HS_ID
 * PB14 : USB1_OTG_HS_DM   (internal PHY)
 * PB15 : USB1_OTG_HS_DP   (internal PHY)
 *
 * -----------------------------------------------------------------------
 * ETHERNET MAC (AF11)
 * -----------------------------------------------------------------------
 * PA1  : ETH_REF_CLK / ETH_RX_CLK
 * PA2  : ETH_MDIO
 * PA3  : ETH_COL
 * PA7  : ETH_CRS_DV / ETH_RX_DV
 * PB0  : ETH_RXD2
 * PB1  : ETH_RXD3
 * PB5  : ETH_PPS_OUT
 * PB8  : ETH_TXD3
 * PB10 : ETH_RX_ER
 * PB11 : ETH_TX_EN
 * PB12 : ETH_TXD0
 * PB13 : ETH_TXD1
 * PC1  : ETH_MDC
 * PC2  : ETH_TXD2
 * PC3  : ETH_TX_CLK
 * PC4  : ETH_RXD0
 * PC5  : ETH_RXD1
 * PE2  : ETH_TXD3
 * PG8  : ETH_PPS_OUT
 * PG11 : ETH_TX_EN
 * PG12 : ETH_PHY_INTN / ETH_TXD1 (RMII)
 * PG13 : ETH_TXD0
 * PG14 : ETH_TXD1
 *
 * -----------------------------------------------------------------------
 * QUADSPI (AF9 / AF10)
 * -----------------------------------------------------------------------
 * PB2  : QUADSPI_CLK
 * PB6  : QUADSPI_BK1_NCS
 * PB10 : QUADSPI_BK1_NCS (AF9)
 * PC9  : QUADSPI_BK1_IO0 (AF9)
 * PC10 : QUADSPI_BK1_IO1 (AF9)
 * PC11 : QUADSPI_BK2_NCS (AF9)
 * PD11 : QUADSPI_BK1_IO0
 * PD12 : QUADSPI_BK1_IO1
 * PD13 : QUADSPI_BK1_IO3
 * PE2  : QUADSPI_BK1_IO2
 * PE7  : QUADSPI_BK2_IO0
 * PE8  : QUADSPI_BK2_IO1
 * PE9  : QUADSPI_BK2_IO2
 * PE10 : QUADSPI_BK2_IO3
 * PF6  : QUADSPI_BK1_IO3
 * PF7  : QUADSPI_BK1_IO2
 * PF8  : QUADSPI_BK1_IO0
 * PF9  : QUADSPI_BK1_IO1
 * PF10 : QUADSPI_CLK
 * PG6  : QUADSPI_BK1_NCS
 * PG9  : QUADSPI_BK2_IO2 (AF9)
 * PG14 : QUADSPI_BK2_IO3 (AF9)
 *
 * -----------------------------------------------------------------------
 * FMC — Flexible Memory Controller (AF12)
 * -----------------------------------------------------------------------
 * PD0  : FMC_D2
 * PD1  : FMC_D3
 * PD3  : FMC_CLK
 * PD4  : FMC_NOE
 * PD5  : FMC_NWE
 * PD6  : FMC_NWAIT
 * PD7  : FMC_NE1
 * PD8  : FMC_D13
 * PD9  : FMC_D14
 * PD10 : FMC_D15
 * PD11 : FMC_A16
 * PD12 : FMC_A17
 * PD13 : FMC_A18
 * PD14 : FMC_D0
 * PD15 : FMC_D1
 * PE0  : FMC_NBL0
 * PE1  : FMC_NBL1
 * PE2  : FMC_A23
 * PE3  : FMC_A19
 * PE4  : FMC_A20
 * PE5  : FMC_A21
 * PE6  : FMC_A22
 * PE7  : FMC_D4
 * PE8  : FMC_D5
 * PE9  : FMC_D6
 * PE10 : FMC_D7
 * PE11 : FMC_D8
 * PE12 : FMC_D9
 * PE13 : FMC_D10
 * PE14 : FMC_D11
 * PE15 : FMC_D12
 * PF0  : FMC_A0
 * PF1  : FMC_A1
 * PF2  : FMC_A2
 * PF3  : FMC_A3
 * PF4  : FMC_A4
 * PF5  : FMC_A5
 * PF11 : FMC_SDNRAS
 * PF12 : FMC_A6
 * PF13 : FMC_A7
 * PF14 : FMC_A8
 * PF15 : FMC_A9
 * PG0  : FMC_A10
 * PG1  : FMC_A11
 * PG2  : FMC_A12
 * PG3  : FMC_A13
 * PG4  : FMC_A14 / FMC_BA0
 * PG5  : FMC_A15 / FMC_BA1
 * PG6  : FMC_NE3
 * PG7  : FMC_INT
 * PG8  : FMC_SDCLK
 * PG9  : FMC_NE2
 * PG10 : FMC_NE3
 * PG11 : FMC_SDNKE
 * PG12 : FMC_NE4
 * PG13 : FMC_A24
 * PG14 : FMC_A25
 * PG15 : FMC_SDNCAS
 * PH2  : FMC_SDCKE0
 * PH3  : FMC_SDNE0
 * PH5  : FMC_SDNWE
 * PH6  : FMC_SDNE1
 * PH7  : FMC_SDCKE1
 * PH8  : FMC_D16
 * PH9  : FMC_D17
 * PH10 : FMC_D18
 * PH11 : FMC_D19
 * PH12 : FMC_D20
 * PH13 : FMC_D21
 * PH14 : FMC_D22
 * PH15 : FMC_D23
 * PI0  : FMC_D24
 * PI1  : FMC_D25
 * PI2  : FMC_D26
 * PI3  : FMC_D27
 * PI4  : FMC_NBL2
 * PI5  : FMC_NBL3
 * PI6  : FMC_D28
 * PI7  : FMC_D29
 * PI9  : FMC_D30
 * PI10 : FMC_D31
 *
 * -----------------------------------------------------------------------
 * DCMI — Digital Camera Interface (AF13)
 * -----------------------------------------------------------------------
 * PA4  : DCMI_HSYNC
 * PA6  : DCMI_PIXCLK
 * PB5  : DCMI_D10
 * PB6  : DCMI_D5
 * PB7  : DCMI_VSYNC
 * PB8  : DCMI_D6
 * PB9  : DCMI_D7
 * PC6  : DCMI_D0
 * PC7  : DCMI_D1
 * PC8  : DCMI_D2
 * PC9  : DCMI_D3
 * PC10 : DCMI_D8
 * PC11 : DCMI_D4
 * PC12 : DCMI_D9
 * PD2  : DCMI_D11
 * PD3  : DCMI_D5
 * PE0  : DCMI_D2
 * PE1  : DCMI_D3
 * PE4  : DCMI_D4
 * PE5  : DCMI_D6
 * PE6  : DCMI_D7
 * PG9  : DCMI_VSYNC
 * PG10 : DCMI_D2
 * PG11 : DCMI_D3
 * PH2  : DCMI_HSYNC
 * PH3  : DCMI_D1
 * PH6  : DCMI_D8
 * PH7  : DCMI_D9
 * PH8  : DCMI_HSYNC
 * PH9  : DCMI_D0
 * PH10 : DCMI_D1
 * PH11 : DCMI_D2
 * PH12 : DCMI_D3
 * PH14 : DCMI_D4
 * PI4  : DCMI_D5
 * PI5  : DCMI_VSYNC
 * PI6  : DCMI_D6
 * PI7  : DCMI_D7
 *
 * -----------------------------------------------------------------------
 * LCD-TFT (LTDC) (AF14)
 * -----------------------------------------------------------------------
 * PA1  : LCD_R2
 * PA2  : LCD_R1
 * PA3  : LCD_B5
 * PA4  : LCD_VSYNC
 * PA5  : LCD_R4
 * PA6  : LCD_G2
 * PA7  : LCD_R3 (not all packages)
 * PA8  : LCD_R6
 * PA9  : LCD_R5
 * PA10 : LCD_B1
 * PA11 : LCD_R4
 * PB0  : LCD_R3
 * PB1  : LCD_R6
 * PB8  : LCD_B6
 * PB9  : LCD_B7
 * PB10 : LCD_G4
 * PB11 : LCD_G5
 * PC0  : LCD_R5
 * PC6  : LCD_HSYNC
 * PC7  : LCD_G6
 * PC9  : LCD_B2 (AF10)
 * PC10 : LCD_R2 (AF14)
 * PD3  : LCD_G7
 * PD6  : LCD_B2
 * PE4  : LCD_B0
 * PE5  : LCD_G0
 * PE6  : LCD_G1
 * PE11 : LCD_G3
 * PE12 : LCD_B4
 * PE13 : LCD_DE
 * PE14 : LCD_CLK
 * PE15 : LCD_R7
 * PF10 : LCD_DE
 * PG6  : LCD_R7
 * PG7  : LCD_CLK
 * PG10 : LCD_G3
 * PG11 : LCD_B3
 * PG12 : LCD_B1 (AF9)
 * PH2  : LCD_R0
 * PH3  : LCD_R1
 * PH8  : LCD_R2
 * PH9  : LCD_R3
 * PH10 : LCD_R4
 * PH11 : LCD_R5
 * PH12 : LCD_R6
 * PH13 : LCD_G2
 * PH14 : LCD_G3
 * PH15 : LCD_G4
 * PI0  : LCD_G5
 * PI1  : LCD_G6
 * PI2  : LCD_G7
 * PI4  : LCD_B4
 * PI5  : LCD_B5
 * PI6  : LCD_B6
 * PI7  : LCD_B7
 * PI9  : LCD_VSYNC
 * PI10 : LCD_HSYNC
 * PJ0  : LCD_R7 (LQFP176+)
 * PK7  : LCD_DE (LQFP176+)
 *
 * -----------------------------------------------------------------------
 * AF15 : EVENTOUT
 * -----------------------------------------------------------------------
 * Available on all GPIO pins. Outputs a Cortex-M7 EVENTOUT signal.
 *
 * =============================================================================
 * NOTE: Package-dependent pins (PJ, PK, PI, PH) are only available on
 *       LQFP144 / LQFP176 / TFBGA240 packages. The Daisy Seed uses the
 *       STM32H750IBK6 (TFBGA176) — verify pin availability against Table 7
 *       of DS12556 Rev 7 for your exact package.
 * =============================================================================
 */