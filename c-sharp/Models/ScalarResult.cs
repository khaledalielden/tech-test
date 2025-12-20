using System;

namespace HmxLabs.TechTest.Models
{
    public class ScalarResult
    {
        public ScalarResult(string tradeId_, double? result_, string? error_)
        {
            if (string.IsNullOrWhiteSpace(tradeId_))
            {
                throw new ArgumentException("A non null, non empty trade id must be provided");
            }

            TradeId = tradeId_;
            Result = result_;
            Error = error_;
        }

        public string TradeId { get; private set; }

        public double? Result { get; private set; }

        public string? Error { get; private set; }
    }
}
