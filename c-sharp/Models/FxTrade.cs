using System;

namespace HmxLabs.TechTest.Models
{
    public class FxTrade : BaseTrade
    {
        public const string FxSpotTradeType = "FxSpot";
        public const string FxForwardTradeType = "FxFwd";

        public override string TradeType
        {
            get { throw new NotImplementedException(); }
        }

        public DateTime ValueDate { get; set; }
    }
}
