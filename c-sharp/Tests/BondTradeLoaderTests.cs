using HmxLabs.TechTest.Loaders;
using HmxLabs.TechTest.Models;
using NUnit.Framework;

namespace HmxLabs.TechTest.Tests
{
    [TestFixture]
    public class BondTradeLoaderTests
    {
        [SetUp]
        public void LoadTrades()
        {
            var loader = new BondTradeLoader {DataFile = @"TradeData/BondTrades.dat"};
            var trades = loader.LoadTrades();
            _tradeList = new TradeList(trades);
        }

        [Test]
        public void TestTradeLoadCount()
        {
            Assert.That(_tradeList!.Count, Is.EqualTo(10));
        }

        [Test]
        public void TestTradeLoadAccuracyOfFirstTrade()
        {
            Assert.That(_tradeList![0], Is.TypeOf(typeof(BondTrade)));

            var trade = (BondTrade) _tradeList[0];
            Assert.That(trade.TradeType, Is.EqualTo(BondTrade.GovBondTradeType));
            Assert.That(trade.TradeDate, Is.EqualTo(new DateTime(2012,4,17)));
            Assert.That(trade.Instrument, Is.EqualTo("DE0001117794"));
            Assert.That(trade.Counterparty, Is.EqualTo("CSI¬AG"));
            Assert.That(trade.Notional, Is.EqualTo(674500000));
            Assert.That(trade.Rate, Is.EqualTo(105.985));
            Assert.That(trade.TradeId, Is.EqualTo("GOV001"));
        }

        [Test]
        public void TestTradeLoadAccuracyOfLastTrade()
        {
            Assert.That(_tradeList![8], Is.TypeOf(typeof(BondTrade)));

            var trade = (BondTrade)_tradeList[8];
            Assert.That(trade.TradeType, Is.EqualTo(BondTrade.CorpBondTradeType));
            Assert.That(trade.TradeDate, Is.EqualTo(new DateTime(2012, 8, 30)));
            Assert.That(trade.Instrument, Is.EqualTo("XS0340495216"));
            Assert.That(trade.Counterparty, Is.EqualTo("BLKROCK"));
            Assert.That(trade.Notional, Is.EqualTo(67000000));
            Assert.That(trade.Rate, Is.EqualTo(120.240));
            Assert.That(trade.TradeId, Is.EqualTo("CORP003"));
        }

        private TradeList? _tradeList;
    }
}