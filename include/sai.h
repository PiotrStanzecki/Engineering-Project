#ifndef SAI_H
#define SAI_H

#include "stm32h750xx.h"
#include <stdint.h>



typedef enum {
    SAI_ERROR = 0,
    SAI_SUCCESS
} sai_status;

typedef enum {
    SAI_MODE_MASTER_TX = 0,
    SAI_MODE_MASTER_RX = 1,
    SAI_MODE_SLAVE_TX  = 2,
    SAI_MODE_SLAVE_RX  = 3
} sai_mode;

typedef enum {
    SAI_SYNC_ASYNC    = 0,
    SAI_SYNC_INTERNAL = 1,
    SAI_SYNC_EXTERNAL = 2
} sai_sync;

typedef enum {
    SAI_DATASIZE_8B  = 2,
    SAI_DATASIZE_10B = 3,
    SAI_DATASIZE_16B = 4,
    SAI_DATASIZE_20B = 5,
    SAI_DATASIZE_24B = 6,
    SAI_DATASIZE_32B = 7
} sai_datasize;

typedef enum {
    SAI_PROTOCOL_I2S_PHILIPS = 0,
    SAI_PROTOCOL_LEFT_JUSTIFIED,
    SAI_PROTOCOL_LSB_JUSTIFIED
} sai_protocol;

typedef enum {
    SAI_CH_STEREO = 0,
    SAI_CH_MONO   = 1
} sai_channel_mode;

typedef enum {
    SAI_SLOT_SIZE_16B = 16,
    SAI_SLOT_SIZE_32B = 32
} sai_slot_size;

typedef enum {
    SAI_MCLK_DISABLE = 0,
    SAI_MCLK_ENABLE  = 1
} sai_mclk_enable;

typedef enum {
    SAI_DMA_NORMAL   = 0,
    SAI_DMA_CIRCULAR = 1
} sai_dma_mode;

typedef void (*sai_dma_callback_t)(void);

typedef struct {
    DMA_Stream_TypeDef* stream;
    uint32_t            dmamux_req;
    sai_dma_mode        mode;
    sai_dma_callback_t  half_cplt_cb;
    sai_dma_callback_t  cplt_cb;
} sai_dma_handle_t;

typedef struct {
    SAI_Block_TypeDef* instance;
    sai_mode           mode;
    sai_sync           sync_en;
    sai_protocol       protocol;
    sai_datasize       data_size;
    sai_channel_mode   channel;
    uint8_t            slot_count;
    sai_slot_size      slot_size;
    sai_mclk_enable    mclk_enable;
    uint8_t            mclk_div;
    uint8_t            dma_enabled;
} sai_init_s;

sai_status sai_init(const sai_init_s* sai);
sai_status sai_transmit(SAI_Block_TypeDef* sai_block, const uint32_t* data, uint16_t size, uint32_t timeout);
sai_status sai_receive(SAI_Block_TypeDef* sai_block, uint32_t* data, uint16_t size, uint32_t timeout);
sai_status sai_start_dma(SAI_Block_TypeDef* sai_block, sai_dma_handle_t* handle);
sai_status sai_transmit_dma(SAI_Block_TypeDef* sai_block, const uint32_t* data, uint16_t size);
sai_status sai_receive_dma(SAI_Block_TypeDef* sai_block, uint32_t* data, uint16_t size);
sai_status sai_stop_dma(SAI_Block_TypeDef* sai_block);
void sai_dma_irq_handler(SAI_Block_TypeDef* sai_block);



#endif /* SAI_H */
