from django.urls import path
from .views import create, status, index, ask

urlpatterns = [
    path('create', create),
    path('status/<str:task_uid>', status),
    path('index', index, name='index'),
    path('ask/', ask, name='ask')
]
