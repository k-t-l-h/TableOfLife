from rest_framework.decorators import api_view
from .forms import AskForm
from django.shortcuts import render
from django.http import JsonResponse
from rest_framework import status
import requests
import json


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
    if request.method == "POST":
        try:
            uuid = None
            jsonR = '{ "classes":  ['
            form = AskForm(request.POST)
            if form.is_valid():
                quest = request.POST['classes'].split('; ')
                set = request.POST['settings'].split(', ')
                q = 0
                for i in quest:
                    qw = i.split(', ')
                    q += 1
                    jsonR += ' {' + '"id_groups": ' + str(q) + ', "name": ' + '"' + qw[0] + '", "teacher": ' + '"' + \
                             qw[1] + '", "count_students": ' + qw[2] + ' },'

                jsonR = jsonR[:-1]
                jsonR += '], "classesNumber": ' + str(len(quest)) + ',' + '"students": [' + request.POST['students'] + \
                         '], "iterations": 5, "params": { "crossover":' + '"' + set[0] + '",' + ' "mutation":' + \
                         '"' + set[1] + '",' + ' "selector":' + '"' + set[2] + '",' + ' "creator":' + '"' + set[3] + \
                         '" } }'
                d = json.loads(jsonR)
                req = requests.post('http://127.0.0.1:8081/create/', json=d).json()
                if 'UUID' in req:
                    uuid = req['UUID']
                elif 'error' in req:
                    uuid = req['error']
            return render(request, 'app/ask.html', {'form': form, 'UUID': uuid})
        except:
            return render(request, 'app/ask.html', {'form': form, 'UUID': "Ошибка парсера"})
    form = AskForm({'settings': "default, default, default, random"})
    return render(request, 'app/ask.html', {'form': form})
