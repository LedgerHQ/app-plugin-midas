/*******************************************************************************
 *   Plugin Boilerplate
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <string.h>
#include "eth_plugin_interface.h"
// #define PRINTF screen_printf

// All possible selectors of your plugin.
// A Xmacro below will create for you:
//     - an enum named selector_t with every NAME
//     - a map named SELECTORS associating each NAME with it's value
#define SELECTORS_LIST(X)                    \
    X(DEPOSIT_INSTANT, 0xc02dd27a)           \
    X(DEPOSIT_REQUEST, 0x6e26b9f8)           \
    X(REDEEM_INSTANT, 0x8b53f75e)            \
    X(REDEEM_REQUEST, 0xbfc2d46a)            \
    X(REDEEM_FIAT_REQUEST, 0xd5f73f5c)       \

// Xmacro helpers to define the enum and map
// Do not modify !
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,

// This enum will be automatically expanded to hold all selector names.
// The value SELECTOR_COUNT can be used to get the number of defined selectors
// Do not modify !
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
extern const uint32_t SELECTORS[SELECTOR_COUNT];

// Enumeration used to parse the smart contract data.
typedef enum {
    TOKEN_ADDRESS = 0,
    TOKEN_AMOUNT,
    MIN_RECEIVE_AMOUNT,
    UNSUPPORTED_PARAMETER
} parameter;

typedef enum m_product_e{
    M_TBILL,
    M_BASIS    
} m_product_t;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_s {
    // For display.
    bool is_deposit;
    m_product_t m_product;
    uint8_t token_address[ADDRESS_LENGTH];
    char token_ticker[MAX_TICKER_LEN];
    bool token_ticker_found;
    uint8_t token_amount[INT256_LENGTH];
    uint8_t min_receive_amount[INT256_LENGTH];

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.

    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Check if the context structure will fit in the RAM section ETH will prepare for us
// Do not remove!
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}