using System;

namespace HmxLabs.TechTest.Models
{
    public interface ITrade
    {
        DateTime TradeDate { get; set; }

        string? Instrument { get; set; }

        string? Counterparty { get; set; }

        double Notional { get; set; }

        double Rate { get; set; }

        string TradeType { get; }

        string TradeId { get; }
    }
}