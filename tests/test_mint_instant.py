from .utils import MToken,  prepare_tx_params_deposit_instant


class TestDepositInstant:
    def __deposit_instant(self, request, sign_helper, eth_client, m_token):
        tx_params = prepare_tx_params_deposit_instant(eth_client, m_token)
        sign_helper.sign_and_ui_validate(tx_params)

    def test_deposit_instant_m_tbill(self, request, sign_helper, eth_client):
        self.__deposit_instant(request, sign_helper, eth_client, MToken.mTBILL)

    def test_deposit_instant_m_basis(self, request, sign_helper, eth_client):
        self.__deposit_instant(request, sign_helper, eth_client, MToken.mBASIS)
