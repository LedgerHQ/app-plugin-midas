from .utils import MToken,  prepare_tx_params_deposit_request


class TestDepositRequest:
    def __deposit_request(self, request, sign_helper, eth_client, m_token):
        tx_params = prepare_tx_params_deposit_request(eth_client, m_token)
        sign_helper.sign_and_ui_validate(tx_params)

    def test_deposit_request_m_tbill(self, request, sign_helper, eth_client):
        self.__deposit_request(request, sign_helper, eth_client, MToken.mTBILL)

    def test_deposit_request_m_basis(self, request, sign_helper, eth_client):
        self.__deposit_request(request, sign_helper, eth_client, MToken.mBASIS)
