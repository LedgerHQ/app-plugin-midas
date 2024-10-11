from pathlib import Path
import json
import os
import datetime

from web3 import Web3
from eth_typing import ChainId

from ledger_app_clients.ethereum.client import EthAppClient
import ledger_app_clients.ethereum.response_parser as ResponseParser
from ledger_app_clients.ethereum.utils import get_selector_from_data, recover_transaction
from ragger.navigator import NavInsID

from .utils import get_appname_from_makefile, DERIVATION_PATH, load_contracts, prepare_tx_params_deposit_instant, prepare_tx_params_deposit_request, prepare_tx_params_redeem_instant, prepare_tx_params_redeem_request

import logging

ROOT_SCREENSHOT_PATH = Path(__file__).parent
ABIS_FOLDER = "%s/abis" % (os.path.dirname(__file__))

PLUGIN_NAME = get_appname_from_makefile()


logging.basicConfig(level=logging.DEBUG)


def test_deposit_instant_playground(backend, firmware, navigator, test_name, wallet_addr):
    client = EthAppClient(backend)

    tx_params = prepare_tx_params_deposit_instant(client)
    # send the transaction
    with client.sign(DERIVATION_PATH, tx_params):
        print("Playground")

    # verify signature
    vrs = ResponseParser.signature(client.response().data)
    addr = recover_transaction(tx_params, vrs)
    assert addr == wallet_addr.get()



def test_redeem_instant_playground(backend, firmware, navigator, test_name, wallet_addr):
    client = EthAppClient(backend)

    tx_params = prepare_tx_params_redeem_instant(client)
    # send the transaction
    with client.sign(DERIVATION_PATH, tx_params):
        print("Playground")

    # verify signature
    vrs = ResponseParser.signature(client.response().data)
    addr = recover_transaction(tx_params, vrs)
    assert addr == wallet_addr.get()

def test_deposit_request_playground(backend, firmware, navigator, test_name, wallet_addr):
    client = EthAppClient(backend)

    tx_params = prepare_tx_params_deposit_request(client)
    # send the transaction
    with client.sign(DERIVATION_PATH, tx_params):
        print("Playground")

    # verify signature
    vrs = ResponseParser.signature(client.response().data)
    addr = recover_transaction(tx_params, vrs)
    assert addr == wallet_addr.get()


def test_redeem_request_playground(backend, firmware, navigator, test_name, wallet_addr):
    client = EthAppClient(backend)

    tx_params = prepare_tx_params_redeem_request(client)
    # send the transaction
    with client.sign(DERIVATION_PATH, tx_params):
        print("Playground")

    # verify signature
    vrs = ResponseParser.signature(client.response().data)
    addr = recover_transaction(tx_params, vrs)
    assert addr == wallet_addr.get()


# def test_redeem_instant_playground(backend, firmware, navigator, test_name, wallet_addr):
#     client = EthAppClient(backend)

#     tx_params = prepare_tx_params_redeem_instant(client)
#     # send the transaction
#     with client.sign(DERIVATION_PATH, tx_params):
#         print("TEST")
#         # Validate the on-screen request by performing the navigation appropriate for this device
#         # if firmware.is_nano:
#         #     navigator.navigate_until_text(NavInsID.RIGHT_CLICK,
#         #                                               [NavInsID.BOTH_CLICK],
#         #                                               "Accept")
#         # else:
#         #     navigator.navigate_until_text_and_compare(NavInsID.SWIPE_CENTER_TO_LEFT,
#         #                                               [NavInsID.USE_CASE_REVIEW_CONFIRM,
#         #                                                NavInsID.USE_CASE_STATUS_DISMISS],
#         #                                               "Hold to sign",
#         #                                               ROOT_SCREENSHOT_PATH,
#         #                                               test_name)
#     # verify signature
#     vrs = ResponseParser.signature(client.response().data)
#     addr = recover_transaction(tx_params, vrs)
#     assert addr == wallet_addr.get()
