#include "plugin.h"
#define PRINTF screen_printf

void handle_provide_token(ethPluginProvideInfo_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    if (msg->item1) {
        strlcpy(context->token_ticker, (char *) msg->item1->token.ticker, sizeof(context->token_ticker));

        context->token_ticker_found = true;
    } else {
        context->token_ticker_found = false;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
