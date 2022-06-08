from logging import exception
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.http import JsonResponse
from django.http import HttpResponse
from django.shortcuts import render
import requests

def index(request):
    return render(request, 'falculator.html')

@api_view(['POST'])
def fractionSum(request):
    try:
        res = requests.post(
            url="http://localhost:5000/api/calculate/sum",
            json=request.data,
            headers={"Content-Type":"application/json"},
            timeout=3
        )
    except ConnectionRefusedError:
        return Response(status=503) 
    except ConnectionError:
        return Response(status=503) 
    except:
        return Response(status=503)  
    if res.status_code == 201:
        return JsonResponse(res.json())
    else:
        return Response(status=res.status_code)
