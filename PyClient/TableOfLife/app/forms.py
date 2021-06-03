from django.core.exceptions import ValidationError, ObjectDoesNotExist
from django.contrib.auth.models import User
from django.core import validators
from django import forms
import re


class AskForm(forms.Form):
    classes = forms.CharField(label='О предметах:', widget=forms.Textarea(
        attrs={'class': 'form-control', 'rows': 5, 'placeholder': 'Название предмета, Имя преподавателя, Количество студентов'}))
    students = forms.CharField(label='Выбор учеников:', widget=forms.Textarea(
        attrs={'class': 'form-control', 'rows': 5, 'placeholder': 'Матрица оценок'}))
    settings = forms.CharField(label='Настройка (только для продвинутых): crossover, mutation, selector, creator', widget=forms.TextInput(
        attrs={'class': 'form-control', 'placeholder': 'Указывайте через запятую'}))


class PostForm(forms.Form):
    uuid = forms.CharField(label='Ваш UUID:', widget=forms.TextInput(
        attrs={'class': 'form-control', 'rows': 5, 'placeholder': 'UUID'}))
