
from pathlib import Path
from ragger.navigator import NavInsID
from .utils import DERIVATION_PATH
import ledger_app_clients.ethereum.response_parser as ResponseParser
from ledger_app_clients.ethereum.utils import recover_transaction


class SignHelper:
    def __init__(self, client, navigation_helper, wallet_addr):
        self.client = client
        self.wallet_addr = wallet_addr
        self.navigation_helper = navigation_helper

    def sign_and_ui_validate(self, tx_params):
        with self.client.sign(DERIVATION_PATH, tx_params):
            self.navigation_helper.ui_validate()
        
        vrs = ResponseParser.signature(self.client.response().data)
        addr = recover_transaction(tx_params, vrs)
        assert addr == self.wallet_addr.get()
        