using System.Collections.Generic;

namespace HmxLabs.TechTest.Models
{
    public class TradeList : List<ITrade>, ITradeReceiver
    {
        public TradeList()
        {
            
        }

        public TradeList(IEnumerable<ITrade> trades_)
        {
            AddRange(trades_);
        }

        public void AddTrades(IEnumerable<ITrade> trades_)
        {
            AddRange(trades_);
        }
    }
}