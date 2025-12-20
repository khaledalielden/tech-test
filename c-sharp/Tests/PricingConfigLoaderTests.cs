using HmxLabs.TechTest.Models;
using HmxLabs.TechTest.RiskSystem;
using NUnit.Framework;

namespace HmxLabs.TechTest.Tests
{
    [TestFixture]
    public class PricingConfigLoaderTests
    {
        [SetUp]
        public void LoadConfig()
        {
            var loader = new PricingConfigLoader {ConfigFile = @"PricingConfig/PricingEngines.xml"};
            _config = loader.LoadConfig();
        }

        [Test]
        public void TestConfigItemCount()
        {
            Assert.That(_config!.Count, Is.EqualTo(4));
        }

        [Test]
        public void TestFirstConfigMapping()
        {
            var configItem = _config![0];

            Assert.That(configItem.TradeType, Is.EqualTo(BondTrade.GovBondTradeType));
            Assert.That(configItem.TypeName, Is.EqualTo("HmxLabs.TechTest.Pricers.GovBondPricingEngine"));
            Assert.That(configItem.Assembly, Is.EqualTo("HmxLabs.TechTest.Pricers"));
        }

        [Test]
        public void TestLastConfigMapping()
        {
            var configItem = _config![3];
            Assert.That(configItem.TradeType, Is.EqualTo(FxTrade.FxForwardTradeType));
            Assert.That(configItem.TypeName, Is.EqualTo("HmxLabs.TechTest.Pricers.FxPricingEngine"));
            Assert.That(configItem.Assembly, Is.EqualTo("HmxLabs.TechTest.Pricers"));
        }

        private PricingEngineConfig? _config;
    }
}
