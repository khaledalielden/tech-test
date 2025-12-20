using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HmxLabs.TechTest.Models
{
    public interface ITradeEnumerable<T> : IEnumerable<T> where T : ITrade
    {
    }
}
