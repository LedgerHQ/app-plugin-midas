from .utils import MToken,RedemptionVaultType, prepare_tx_params_redeem_request
from types import SimpleNamespace
from .token_metadata_database import UNKN

class TestRedeemRequest:
    def __redeem_request(self, request, sign_helper, eth_client, m_token, vault_type = RedemptionVaultType.REGULAR, params = None):
        tx_params = prepare_tx_params_redeem_request(eth_client, m_token, vault_type, params)
        sign_helper.sign_and_ui_validate(tx_params)

    def test_redeem_request_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mTBILL)

    def test_redeem_request_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mBASIS)

    def test_redeem_request_buidl_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mTBILL, RedemptionVaultType.BUIDL)

    def test_redeem_request_swapper_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mBASIS, RedemptionVaultType.SWAPPER)

    def test_redeem_request_fiat_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mTBILL, RedemptionVaultType.REGULAR, SimpleNamespace(requestFn="redeemFiatRequest"))

    def test_redeem_request_fiat_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mBASIS, RedemptionVaultType.REGULAR, SimpleNamespace(requestFn="redeemFiatRequest"))

    def test_redeem_request_fiat_buidl_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mTBILL, RedemptionVaultType.BUIDL, SimpleNamespace(requestFn="redeemFiatRequest"))

    def test_redeem_request_fiat_swapper_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mBASIS, RedemptionVaultType.SWAPPER, SimpleNamespace(requestFn="redeemFiatRequest"))
    
    def test_redeem_request_m_tbill_unknown_payment_token(self, request, sign_helper, eth_client):
        self.__redeem_request(request, sign_helper, eth_client, MToken.mBASIS, RedemptionVaultType.REGULAR, SimpleNamespace(token=UNKN))

    
