using CSCalculateFractionsWrapperDll;
using System.Net;
using System.Text.Json;
using System.Text.Json.Serialization;

// Dependancy check
if (true)
{
    CFraction frac1 = new CFraction(0, 1);
    frac1.Dispose();
}

var builder = WebApplication.CreateBuilder(args);

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/error-development");
}
else
{
    app.UseExceptionHandler("/error");
}

app.MapPost("/api/calculate/sum", async context =>
{
    if (!context.Request.HasJsonContentType())
    {
        context.Response.StatusCode = (int)HttpStatusCode.UnsupportedMediaType;
        return;
    }
    try
    {
        RequestObj obj = await context.Request.ReadFromJsonAsync<RequestObj>();

        context.Response.StatusCode = (int)HttpStatusCode.Created;
        CFraction sum = SumFractions(obj.fractions);
        SimpleFraction returnFrac = new SimpleFraction();
        returnFrac.numerator = (short)sum.Numerator;
        returnFrac.denominator = (short)sum.Denominator;
        returnFrac.sign = (short)sum.Sign;
        sum.Dispose();
        string myJsonObj = JsonSerializer.Serialize(returnFrac);
        context.Response.ContentType = "application/json"; 
        await context.Response.WriteAsync(myJsonObj);
        Console.WriteLine(myJsonObj);
    }
    catch (System.Text.Json.JsonException e)
    {
        Console.WriteLine(e.Message);
        context.Response.StatusCode = (int)HttpStatusCode.UnprocessableEntity;
        return;
    }
    catch (System.ArgumentOutOfRangeException e)
    {
        Console.WriteLine(e.Message);
        context.Response.StatusCode = (int)HttpStatusCode.BadRequest;
        return;
    }
    catch (SystemException e)
    {
        Console.WriteLine(e.Message);
        context.Response.StatusCode = (int)HttpStatusCode.InternalServerError;
        return;
    }
});

app.Run("http://localhost:5000"); ;

CFraction SumFractions(List<SimpleFraction> simpleFractions)
{
    CFraction sumFraction = new CFraction(0, 1);
    CFraction tempFrac = new CFraction();
    foreach (SimpleFraction frac in simpleFractions)
    {
        frac.sign = (short)Math.Clamp((int)frac.sign, -1, 1);
        tempFrac.SetFraction((short)(frac.numerator * frac.sign), frac.denominator);
        sumFraction = sumFraction + tempFrac;
    }
    tempFrac.Dispose();
    return sumFraction;
}

public class SimpleFraction
{
    public short numerator { get; set; }
    public short denominator { get; set; }
    public short sign { get; set; }
}
public class RequestObj
{
    public List<SimpleFraction>? fractions { get; set; }
}
