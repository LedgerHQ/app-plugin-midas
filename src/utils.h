#include "eth_plugin_interface.h"
#include "contracts.h"
// #define PRINTF screen_printf

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}
static inline m_product_t determine_product_type(uint8_t *contract_address) {
    // TODO: remove
    // printf_hex_array("determine_product_type 1", ADDRESS_LENGTH, contract_address);
    // printf_hex_array("determine_product_type 2", ADDRESS_LENGTH, m_tbill_redemption_vault_address);
    // PRINTF("determine_product_type 3, %d", memcmp(m_tbill_redemption_vault_address, contract_address, ADDRESS_LENGTH));

    return 
        memcmp(m_tbill_deposit_vault_address, contract_address, ADDRESS_LENGTH) == 0 ||
        memcmp(m_tbill_redemption_vault_address, contract_address, ADDRESS_LENGTH) == 0 ||
        memcmp(m_tbill_redemption_buidl_vault_address, contract_address, ADDRESS_LENGTH) == 0
            ? M_TBILL 
            : M_BASIS;
}