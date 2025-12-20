namespace HmxLabs.TechTest.Pricers
{
    public class CorpBondPricingEngine : BasePricingEngine
    {
        public CorpBondPricingEngine()
        {
            Delay = 8000;
            AddSupportedTradeType("CorpBond");
        }
    }
}