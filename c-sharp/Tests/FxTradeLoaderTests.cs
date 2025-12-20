using System;
using HmxLabs.TechTest.Loaders;
using HmxLabs.TechTest.Models;
using NUnit.Framework;

namespace HmxLabs.TechTest.Tests
{
    [TestFixture]
    public class FxTradeLoaderTests
    {
        [SetUp]
        public void LoadTrades()
        {
            var loader = new FxTradeLoader { DataFile = @"TradeData/FxTrades.dat" };
            var trades = loader.LoadTrades();
            _tradeList = new TradeList(trades);
        }

        [Test]
        public void TestTradeLoadCount()
        {
            Assert.That(_tradeList!.Count, Is.EqualTo(4));
        }

        [Test]
        public void TestTradeLoadAccuracyOfFirstTrade()
        {
            Assert.That(_tradeList![0], Is.TypeOf<FxTrade>());

            var trade = (FxTrade)_tradeList[0];
            Assert.That(trade.TradeType, Is.EqualTo(FxTrade.FxSpotTradeType));
            Assert.That(trade.TradeDate, Is.EqualTo(new DateTime(2012, 10, 08)));
            Assert.That(trade.Instrument, Is.EqualTo("EURUSD"));
            Assert.That(trade.Counterparty, Is.EqualTo("CSI,AG"));
            Assert.That(trade.Notional, Is.EqualTo(145000000));
            Assert.That(trade.Rate, Is.EqualTo(0.97562));
            Assert.That(trade.ValueDate, Is.EqualTo(new DateTime(2012, 10, 11)));
        }

        [Test]
        public void TestTradeLoadAccuracyOfLastTrade()
        {
            Assert.That(_tradeList![3], Is.TypeOf<FxTrade>());

            var trade = (FxTrade)_tradeList[3];
            Assert.That(trade.TradeType, Is.EqualTo(FxTrade.FxForwardTradeType));
            Assert.That(trade.TradeDate, Is.EqualTo(new DateTime(2012, 05, 09)));
            Assert.That(trade.Instrument, Is.EqualTo("USDJPY"));
            Assert.That(trade.Counterparty, Is.EqualTo("GS"));
            Assert.That(trade.Notional, Is.EqualTo(1223445000));
            Assert.That(trade.Rate, Is.EqualTo(78.983));
            Assert.That(trade.ValueDate, Is.EqualTo(new DateTime(2012, 07, 16)));
        }

        private TradeList? _tradeList;
    }
}
