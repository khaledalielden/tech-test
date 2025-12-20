namespace HmxLabs.TechTest.Pricers
{
    public class GovBondPricingEngine : BasePricingEngine
    {
        public GovBondPricingEngine()
        {
            Delay = 5000;
            AddSupportedTradeType("GovBond");
        }
    }
}
