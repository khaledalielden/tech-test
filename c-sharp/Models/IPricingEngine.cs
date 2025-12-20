namespace HmxLabs.TechTest.Models
{
    public interface IPricingEngine
    {
        void Price(ITrade trade_, IScalarResultReceiver resultReceiver_);
    }
}
