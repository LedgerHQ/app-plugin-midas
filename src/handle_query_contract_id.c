#include "plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, APPNAME, msg->nameLength);

    if (context->selectorIndex == DEPOSIT_INSTANT) {
        strlcpy(msg->version, "Mint Instant", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == REDEEM_INSTANT) {
        strlcpy(msg->version, "Redeem Instant", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == DEPOSIT_REQUEST) {
        strlcpy(msg->version, "Mint Request", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == REDEEM_REQUEST || context->selectorIndex == REDEEM_FIAT_REQUEST) {
        strlcpy(msg->version, "Redeem Request", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else {
        PRINTF("Selector index: %d not supported\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}
