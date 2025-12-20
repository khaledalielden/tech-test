using HmxLabs.TechTest.Models;

namespace HmxLabs.TechTest.Loaders
{
    public interface ITradeLoader
    {
        IEnumerable<ITrade> LoadTrades();

        string? DataFile { get; set; }
    }
}