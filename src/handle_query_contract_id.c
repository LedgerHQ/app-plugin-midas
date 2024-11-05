#include "plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, APPNAME, msg->nameLength);

    switch (context->selectorIndex) {
        case DEPOSIT_INSTANT:
            strlcpy(msg->version, "Instant Buy", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case REDEEM_INSTANT:
            strlcpy(msg->version, "Instant Redeem", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case DEPOSIT_REQUEST:
            strlcpy(msg->version, "Buy Request", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case REDEEM_REQUEST:
        case REDEEM_FIAT_REQUEST:
            strlcpy(msg->version, "Redeem Request", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}
