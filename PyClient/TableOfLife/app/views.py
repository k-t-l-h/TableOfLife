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
        a = request
        return JsonResponse({'detail': '{}'.format('d0415ca1-dfaa-40ae-adad-f242197d490b')}, status=200)
    except Exception as e:
        return JsonResponse({'message': '{}'.format(e)}, status=400)
