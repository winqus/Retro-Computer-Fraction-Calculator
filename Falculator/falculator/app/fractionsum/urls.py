from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='falculator'),
    path('api/sum', views.fractionSum, name='falculatorSum')
]