#include "plugin.h"

void handle_provide_token(ethPluginProvideInfo_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    PRINTF("Plugin provide tokens : 0x%p, 0x%p\n", msg->item1, msg->item2);

    if (msg->item1) {
        strlcpy(context->token_ticker, (char *) msg->item1->token.ticker, sizeof(context->token_ticker));

        context->token_ticker_found = true;
    } else {
        context->token_ticker_found = false;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
