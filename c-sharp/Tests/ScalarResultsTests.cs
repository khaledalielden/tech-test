using System.Linq;
using HmxLabs.TechTest.Models;
using NUnit.Framework;

namespace HmxLabs.TechTest.Tests
{
    [TestFixture]
    public class ScalarResultsTests
    {
        [Test]
        public void TestResultInsertion()
        {
            var results = new ScalarResults();
            results.AddResult(DummyTradeIdOne, DummyResultOne);

            var result = results[DummyTradeIdOne];
            Assert.That(result!.TradeId, Is.EqualTo(DummyTradeIdOne));
            Assert.That(result.Result, Is.EqualTo(DummyResultOne));
        }

        [Test]
        public void TestErrorInsertion()
        {
            var results = new ScalarResults();
            results.AddError(DummyTradeIdOne, DummyErrorOne);

            var result = results[DummyTradeIdOne];
            Assert.That(result!.TradeId, Is.EqualTo(DummyTradeIdOne));
            Assert.That(result.Error, Is.EqualTo(DummyErrorOne));
        }

        [Test]
        public void TestCombinedErrorAndResultInsertion()
        {
            var results = new ScalarResults();
            results.AddResult(DummyTradeIdOne, DummyResultOne);
            results.AddError(DummyTradeIdOne, DummyErrorOne);

            var result = results[DummyTradeIdOne];
            Assert.That(result!.TradeId, Is.EqualTo(DummyTradeIdOne));
            Assert.That(result.Error, Is.EqualTo(DummyErrorOne));
            Assert.That(result.Result, Is.EqualTo(DummyResultOne));
        }

        [Test]
        public void TestContainsPositive()
        {
            var results = new ScalarResults();
            results.AddError(DummyTradeIdOne, DummyErrorOne);
            Assert.That(results.ContainsTrade(DummyTradeIdOne), Is.True);

            results = new ScalarResults();
            results.AddResult(DummyTradeIdOne, DummyResultOne);
            Assert.That(results.ContainsTrade(DummyTradeIdOne), Is.True);
        }

        [Test]
        public void TestContainsNegative()
        {
            var results = new ScalarResults();
            results.AddError(DummyTradeIdOne, DummyErrorOne);
            Assert.That(results.ContainsTrade(DummyTradeIdTwo), Is.False);

            results = new ScalarResults();
            results.AddResult(DummyTradeIdOne, DummyResultTwo);
            Assert.That(results.ContainsTrade(DummyTradeIdTwo), Is.False);
        }

        [Test]
        public void TestEnumeration()
        {
            var results = new ScalarResults();
            results.AddResult(DummyTradeIdOne, DummyResultOne);
            results.AddError(DummyTradeIdOne, DummyErrorOne);
            results.AddResult(DummyTradeIdTwo, DummyResultTwo);
            results.AddError(DummyTradeIdTwo, DummyErrorTwo);
            results.AddResult(DummyTradeIdThree, DummyResultThree);
            results.AddError(DummyTradeIdFour, DummyErrorFour);

            var resultsList = results.ToList();
            Assert.That(resultsList.Count, Is.EqualTo(4));

            var dummyResult = resultsList.First(res_ => res_.TradeId == DummyTradeIdOne);
            Assert.That(dummyResult, Is.Not.Null);
            Assert.That(dummyResult.Result, Is.EqualTo(DummyResultOne));
            Assert.That(dummyResult.Error, Is.EqualTo(DummyErrorOne));

            dummyResult = resultsList.First(res_ => res_.TradeId == DummyTradeIdTwo);
            Assert.That(dummyResult, Is.Not.Null);
            Assert.That(dummyResult.Result, Is.EqualTo(DummyResultTwo));
            Assert.That(dummyResult.Error, Is.EqualTo(DummyErrorTwo));

            dummyResult = resultsList.First(res_ => res_.TradeId == DummyTradeIdThree);
            Assert.That(dummyResult, Is.Not.Null);
            Assert.That(dummyResult.Result, Is.EqualTo(DummyResultThree));
            Assert.That(dummyResult.Error, Is.Null);

            dummyResult = resultsList.First(res_ => res_.TradeId == DummyTradeIdFour);
            Assert.That(dummyResult, Is.Not.Null);
            Assert.That(dummyResult.Result.HasValue, Is.False);
            Assert.That(dummyResult.Error, Is.EqualTo(DummyErrorFour));
        }

        private const string DummyTradeIdOne = "TradeOne";
        private const double DummyResultOne = 100.00;
        private const string DummyErrorOne = "ErrorMessageOne";

        private const string DummyTradeIdTwo = "TradeTwo";
        private const double DummyResultTwo = 50.525;
        private const string DummyErrorTwo = "ErrorMessageTwo;";

        private const string DummyTradeIdThree = "TradeThree";
        private const double DummyResultThree = 12.5;

        private const string DummyTradeIdFour = "TradeFour";
        private const string DummyErrorFour = "ErrorMessageFour";
    }
}
