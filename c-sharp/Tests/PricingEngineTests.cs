using HmxLabs.TechTest.Models;
using HmxLabs.TechTest.Pricers;
using NUnit.Framework;

namespace HmxLabs.TechTest.Tests
{
    public class PricingEngineTests
    {
        [Test]
        public void TestPricerTypeConfig()
        {
            var govBondPricer = new GovBondPricingEngine();
            Assert.That(govBondPricer.IsTradeTypeSupported(BondTrade.GovBondTradeType), Is.True);

            var corpBondPricer = new CorpBondPricingEngine();
            Assert.That(corpBondPricer.IsTradeTypeSupported(BondTrade.CorpBondTradeType), Is.True);

            var fxPricer = new FxPricingEngine();
            Assert.That(fxPricer.IsTradeTypeSupported(FxTrade.FxSpotTradeType), Is.True);
            Assert.That(fxPricer.IsTradeTypeSupported(FxTrade.FxForwardTradeType), Is.True);
        }
    }
}
