from rest_framework.decorators import api_view
from django.shortcuts import render
from django.http import JsonResponse
from rest_framework import status
import requests


@api_view(['POST'])
def create(request):
    try:
        data = 1
    except Exception as e:
        return JsonResponse({'message': '{}'.format(e)}, status=400)


@api_view(['GET'])
def status(request, task_uid):
    try:
        resp = requests.get('http://127.0.0.1:8081/status/{}'.format(task_uid)).json()
        return JsonResponse(resp, status=200)
    except Exception as e:
        return JsonResponse({'message': '{}'.format(e)}, status=400)


def index(request):
    return render(request, 'app/index.html')


def ask(request):
    return render(request, 'app/ask.html')