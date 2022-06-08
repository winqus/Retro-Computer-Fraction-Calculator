using System;
using System.Reflection;
using System.Runtime.InteropServices;
namespace CSCalculateFractionsWrapperDll
{
    public class CalculateFractionsBase : IDisposable
    {
        public IntPtr pObject { get; protected set; }
        protected bool disposed = false;
        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;
            // TODO: free unmanaged resources (unmanaged objects) and override finalizer
            if (this.pObject != IntPtr.Zero)
            {
                this.pObject = IntPtr.Zero;
            }
            disposed = true;
            if (disposing)
            {
                // TODO: dispose managed state (managed objects)
            }
        }
        ~CalculateFractionsBase()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: false);
        }

    }
    public class CFraction : CalculateFractionsBase
    {
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern IntPtr cFraction_Create();
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern IntPtr cFraction_CreateWithND(short Numerator, short Denominator);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_Dispose(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_SetFraction(IntPtr p_cFraction, short Numerator, short Denominator);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern uint cFraction_GetNumerator(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern uint cFraction_GetDenominator(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern short cFraction_GetSign(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern double cFraction_GetDecimal(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_ResetFractionCount(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_Assign(IntPtr p_cFraction_FROM, IntPtr p_cFraction_TO);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_PreInc(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFraction_Inc(IntPtr p_cFraction);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern IntPtr cFraction_AddFractions(IntPtr p_cFraction1, IntPtr p_cFraction2);

        public CFraction() => this.pObject = cFraction_Create();
        public CFraction(IntPtr p_cFraction) => this.pObject = p_cFraction;
        public CFraction(short Numerator, short Denominator) => this.pObject = cFraction_CreateWithND(Numerator, Denominator);
        protected override void Dispose(bool disposing)
        {
            if (disposed)
                return;
            if (this.pObject != IntPtr.Zero)
            {
                cFraction_Dispose(this.pObject);
                this.pObject = IntPtr.Zero;
            }
            disposed = true;
            base.Dispose(disposing);
        }
        public void SetFraction(short Numerator, short Denominator) => cFraction_SetFraction(this.pObject, Numerator, Denominator);
        public void ResetFractionCount() => cFraction_ResetFractionCount(this.pObject);
        public static void Assign(CFraction from, CFraction to) => cFraction_Assign(from.pObject, to.pObject);
        public void PreIncrement() => cFraction_PreInc(this.pObject);
        public void Increment() => cFraction_Inc(this.pObject);
        public uint Numerator { get { return cFraction_GetNumerator(this.pObject); } }
        public uint Denominator { get { return cFraction_GetDenominator(this.pObject); } }
        public short Sign { get { return cFraction_GetSign(this.pObject); } }
        public double Decimal { get { return cFraction_GetDecimal(this.pObject); } }
        public static CFraction operator +(CFraction frac1, CFraction frac2) => new CFraction(cFraction_AddFractions(frac1.pObject, frac2.pObject));
        public static CFraction operator ++(CFraction frac)
        {
            cFraction_PreInc(frac.pObject);
            return new CFraction((short)(frac.Sign * frac.Numerator), (short)(frac.Denominator));
        }

        
    }
    public class CFractionCalculator : CalculateFractionsBase
    {
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern IntPtr cFractionCalculator_Create();
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFractionCalculator_Dispose(IntPtr p_cFractionCalculator);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern void cFractionCalculator_PushFraction(IntPtr p_cFractionCalculator, IntPtr p_cFraction2);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern IntPtr cFractionCalculator_GetSum(IntPtr p_cFractionCalculator);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern uint cFractionCalculator_GetGCD(IntPtr p_cFractionCalculator);
        [DllImport("BridgeForCalculateFractionsDll.dll")] private static extern uint cFractionCalculator_GetLCM(IntPtr p_cFractionCalculator);
        public CFractionCalculator() => this.pObject = cFractionCalculator_Create();
        protected override void Dispose(bool disposing)
        {
            if (disposed)
                return;
            if (this.pObject != IntPtr.Zero)
            {
                cFractionCalculator_Dispose(this.pObject);
                this.pObject = IntPtr.Zero;
            }
            disposed = true;
            base.Dispose(disposing);
        }

        public void PushFraction(CFraction fraction) => cFractionCalculator_PushFraction(this.pObject, fraction.pObject);
        public CFraction GetSum() => new CFraction(cFractionCalculator_GetSum(this.pObject));
        public uint GetGCD() => cFractionCalculator_GetGCD(this.pObject);
        public uint GetLCM() => cFractionCalculator_GetLCM(this.pObject);
        
        public CFraction Sum { get { return GetSum(); } }
        public uint GCD { get { return GetGCD(); } }
        public uint LCM { get { return GetLCM(); } }
    }
}