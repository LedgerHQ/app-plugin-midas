class TokenMetadata:
	def __init__(self, ticker, address, decimals, chain_id, supported = True):
		self.ticker = ticker
		self.address = address
		self.decimals = decimals
		self.chain_id = chain_id
		self.supported = supported

USDT = TokenMetadata("USDT", "dac17f958d2ee523a2206206994597c13d831ec7", 6, 1)
USDC = TokenMetadata("USDC", "A0b86991c6218b36c1d19D4a2e9Eb0cE3606eB48", 6, 1)
UNKN = TokenMetadata("UNKN", "0000000000000000000000000000000000000000", 18, 1, False)