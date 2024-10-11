#include "plugin.h"
// #define PRINTF screen_printf

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->numScreens = 1;

    switch(context->selectorIndex) { 
        case DEPOSIT_INSTANT:
        case REDEEM_INSTANT: 
            msg->numScreens += 2;
            break;
        case DEPOSIT_REQUEST:
        case REDEEM_REQUEST: 
            msg->numScreens += 1;
            break;
        default:
            PRINTF("handle_finalize: unsupported selector index");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    printf_hex_array("Token lookup\n", ADDRESS_LENGTH, context->token_address);
    msg->tokenLookup1 = context->token_address;

    context->m_product = M_TBILL;
    context->is_deposit = true;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
