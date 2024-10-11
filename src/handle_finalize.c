#include "plugin.h"
// #define PRINTF screen_printf

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->numScreens = 1;
    
    context->is_deposit = false;
    context->is_request = false;
    context->is_fiat = false;

    switch(context->selectorIndex) { 
        case DEPOSIT_INSTANT:
            context->is_deposit = true;
        case REDEEM_INSTANT: 
            msg->numScreens += 2;
            break;
        case DEPOSIT_REQUEST:
            context->is_deposit = true;
        case REDEEM_FIAT_REQUEST: 
            context->is_fiat = true;
        case REDEEM_REQUEST: 
            context->is_request = true;
            msg->numScreens += 2;
            break;
        default:
            PRINTF("handle_finalize: unsupported selector index");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    printf_hex_array("Token lookup\n", ADDRESS_LENGTH, context->token_address);
    msg->tokenLookup1 = context->token_address;
    
    // FIXME:
    context->m_product = M_TBILL;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
