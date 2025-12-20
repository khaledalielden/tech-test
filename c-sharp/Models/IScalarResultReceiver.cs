namespace HmxLabs.TechTest.Models
{
    public interface IScalarResultReceiver
    {
        void AddResult(string tradeId_, double result_);

        void AddError(string tradeId_, string error_);
    }
}