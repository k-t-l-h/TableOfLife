from django.urls import path
from .views import create, status

urlpatterns = [
    path('create', create),
    path('status/<str:task_uid>', status)
]
