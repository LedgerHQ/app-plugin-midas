import pytest

from ledger_app_clients.ethereum.client import EthAppClient
from ragger.conftest import configuration
from .utils import WalletAddr
from .navigation_helper import NavigationHelper
from .sign_helper import SignHelper


###########################
### CONFIGURATION START ###
###########################

# You can configure optional parameters by overriding the value of ragger.configuration.OPTIONAL_CONFIGURATION
# Please refer to ragger/conftest/configuration.py for their descriptions and accepted values

configuration.OPTIONAL.MAIN_APP_DIR = "tests/.test_dependencies/"

configuration.OPTIONAL.BACKEND_SCOPE = "class"


#########################
### CONFIGURATION END ###
#########################

# Pull all features from the base ragger conftest using the overridden configuration
pytest_plugins = ("ragger.conftest.base_conftest", )
            
@pytest.fixture
def wallet_addr(backend):
    return WalletAddr(backend)

@pytest.fixture(scope=configuration.OPTIONAL.BACKEND_SCOPE)
def additional_speculos_arguments():
    return ["--log-level", "usb:DEBUG","--log-level", "speculos:DEBUG", "--log-level", "seproxyhal:DEBUG"]

@pytest.fixture(scope="function")
def eth_client(backend):
    return EthAppClient(backend)

@pytest.fixture(scope="function")
def navigation_helper(navigator, firmware, test_name):
    return NavigationHelper(navigator, firmware, test_name)

@pytest.fixture(scope="function")
def sign_helper(eth_client, navigation_helper, wallet_addr):
    return SignHelper(eth_client, navigation_helper, wallet_addr )