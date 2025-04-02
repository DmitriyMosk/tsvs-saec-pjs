set terminal wxt 0              # Устанавливаем терминал для отображения графика
set autoscale                   # Автоматическое масштабирование осей
set xlabel 'Ось t Time'              # Подпись для оси X
set ylabel 'Ось S(t) Signal'              # Подпись для оси Y
plot 'data.txt' using 1:2 with lines title 'Данные в реальном времени'
pause 1                         # Пауза в 1 секунду перед обновлением
reread                          # Повторное выполнение скрипта
