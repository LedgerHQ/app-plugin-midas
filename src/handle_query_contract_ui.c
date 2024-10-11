#include "plugin.h"
#define PRINTF screen_printf

// Set UI for the "Product" screen.
static bool set_product_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Product", msg->titleLength);

    return strlcpy(msg->msg, context->m_product == M_BASIS ? "mBASIS" : "mTBILL", msg->msgLength);
}

// // Set UI for "Token" screen.
// // EDIT THIS: Adapt / remove this function to your needs.
static bool set_token_amount_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, context->is_deposit ? "To pay" : "To redeem", msg->titleLength);

    const uint8_t decimals = 18;

    const char *ticker = context->token_ticker;

    // If the token look up failed, use the default unknown ticker
    
    if(context->is_deposit) {
        if (!context->token_ticker_found) {
            // TODO: move to fn
            memset(ticker, 0, MAX_TICKER_LEN);
            strlcpy(ticker, "UNKN", MAX_TICKER_LEN);
        }
    } else {
        // TODO: move to fn
        memset(ticker, 0, MAX_TICKER_LEN);
        // TODO: move mToken name to fn
        strlcpy(ticker, context->m_product == M_BASIS ? "mBASIS" : "mTBILL", MAX_TICKER_LEN);
    }

    return amountToString(context->token_amount,
                          sizeof(context->token_amount),
                          decimals,
                          ticker,
                          msg->msg,
                          msg->msgLength);
}

// // Set UI for "Beneficiary" screen.
// // EDIT THIS: Adapt / remove this function to your needs.
static bool set_min_to_receive_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Min. to receive", msg->titleLength);

    const uint8_t decimals = 18;

    const char *ticker = context->token_ticker;

    // If the token look up failed, use the default unknown ticker
    
    if(!context->is_deposit) {
        if (!context->token_ticker_found) {
            // TODO: move to fn
            memset(ticker, 0, MAX_TICKER_LEN);
            strlcpy(ticker, "UNKN", MAX_TICKER_LEN);
        }
    } else {
        // TODO: move to fn
        memset(ticker, 0, MAX_TICKER_LEN);
        // TODO: move mToken name to fn
        strlcpy(ticker, context->m_product == M_BASIS ? "mBASIS" : "mTBILL", MAX_TICKER_LEN);
    }

    return amountToString(context->min_receive_amount,
                          sizeof(context->min_receive_amount),
                          decimals,
                          ticker,
                          msg->msg,
                          msg->msgLength);
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    // EDIT THIS: Adapt the cases for the screens you'd like to display.
    switch (msg->screenIndex) {
        case 0:
            ret = set_product_ui(msg, context);
            break;
        case 1:
            ret = set_token_amount_ui(msg, context);
            break;
        case 2:
            ret = set_min_to_receive_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
