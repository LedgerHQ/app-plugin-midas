#include "plugin.h"

static void clean_cpy_ticker(char const *dest, const char *ticker) {
    memset((char *) dest, 0, MAX_TICKER_LEN);
    strlcpy((char *) dest, ticker, MAX_TICKER_LEN);
}

static const char *m_product_t_to_ticker(m_product_t m_product) {
    return m_product == M_BASIS ? "mBASIS" : (m_product == M_BTC ? "mBTC" : "mTBILL");
}

// Set UI for the "Product" screen.
static bool set_product_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Product", msg->titleLength);

    return strlcpy(msg->msg, m_product_t_to_ticker(context->m_product), msg->msgLength);
}

// // Set UI for "Token amount" screen.
static bool set_token_amount_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, context->is_deposit ? "To pay" : "To redeem", msg->titleLength);

    char ticker[MAX_TICKER_LEN];

    clean_cpy_ticker(ticker, context->token_ticker);

    // If the token look up failed, use the default unknown ticker

    if (context->is_deposit) {
        if (!context->token_ticker_found) {
            clean_cpy_ticker(ticker, "????");
        }
    } else {
        clean_cpy_ticker(ticker, m_product_t_to_ticker(context->m_product));
    }

    return amountToString(context->token_amount,
                          sizeof(context->token_amount),
                          18,
                          ticker,
                          msg->msg,
                          msg->msgLength);
}

// // Set UI for "Min to receive" screen.
static bool set_redeem_request_out_asset_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "You will receive", msg->titleLength);

    char ticker[MAX_TICKER_LEN];

    clean_cpy_ticker(ticker, context->token_ticker);

    // If the token look up failed, use the default unknown ticker
    if (!context->is_fiat) {
        if (!context->token_ticker_found) {
            clean_cpy_ticker(ticker, "????");
        }
    } else {
        clean_cpy_ticker(ticker, "USD");
    }

    return strlcpy(msg->msg, ticker, msg->msgLength);
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (msg->screenIndex) {
        case 0:
            ret = set_product_ui(msg, context);
            break;
        case 1:
            ret = set_token_amount_ui(msg, context);
            break;
        case 2:
            ret = set_redeem_request_out_asset_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
