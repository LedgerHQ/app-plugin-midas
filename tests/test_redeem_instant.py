from .utils import MToken, RedemptionVaultType, prepare_tx_params_redeem_instant


class TestRedeemInstant:
    def __redeem_instant(self, request, sign_helper, eth_client, m_token, vault_type = RedemptionVaultType.REGULAR):
        tx_params = prepare_tx_params_redeem_instant(eth_client, m_token, vault_type)
        sign_helper.sign_and_ui_validate(tx_params)

    def test_redeem_instant_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_instant(request, sign_helper, eth_client, MToken.mTBILL)

    def test_redeem_instant_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_instant(request, sign_helper, eth_client, MToken.mBASIS)

    def test_redeem_instant_buidl_m_tbill(self, request, sign_helper, eth_client):
        self.__redeem_instant(request, sign_helper, eth_client, MToken.mTBILL, RedemptionVaultType.BUIDL)

    def test_redeem_instant_swapper_m_basis(self, request, sign_helper, eth_client):
        self.__redeem_instant(request, sign_helper, eth_client, MToken.mBASIS, RedemptionVaultType.SWAPPER)
