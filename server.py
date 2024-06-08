import socket
import random
import string
from telegram import Update, ReplyKeyboardMarkup
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters, CallbackContext
import sqlite3
import threading

CHANGED_IP = '127.0.0.1'
def wait_for_string_and_return_ip(target_string):
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        host = '127.0.0.1'
        port = 54321

        server_socket.bind((host, port))
        server_socket.listen(1)

        print(f"Сервер запущен на {host}:{port}")

        conn, addr = server_socket.accept()
        print(f"Подключение от {addr}")

        while True:
            data = conn.recv(1024)
            print(data.decode())
            print(target_string)
            print(data.decode() == target_string)
            if data.decode() == target_string:
                conn.sendall(addr[0].encode())
                conn.close()
                break
            else:
                conn.sendall(b'NOT');

        server_socket.close()
       
        return str(addr[0])




def add_computer_to_db(conn, ip, id, token, info=None):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Computers (ip, id, token, info) VALUES (?, ?, ?, ?)", (ip, id, token, info))
    conn.commit()
    print("Данные успешно добавлены в базу данных")


def send_request(request, update : Update, context : CallbackContext):
    try:
        server_ip = context.user_data['selected_comp']
    except:
        update.message.reply_text("Выберите или добавте компьютер")
        return -1
    server_port = 12345

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('servvvvv', server_ip)
    client_socket.connect((server_ip, server_port))

    client_socket.send(request.encode())

    if request == 'getfile':
        file_data = client_socket.recv(1024)
        response = ""
        try:
            response = "Получен файл:\n" + file_data.decode('cp1251')
        except:
            response = "Получен файл:\n" + file_data.decode('utf8')

    else:
        response = "Запрос отправлен успешно!"

    client_socket.close()
    return response

def start(update: Update, context: CallbackContext) -> None:
    update.message.reply_text("Привет! Я бот-помощник. Для отправки запроса используйте /send_request <запрос>")

def send_request_command(update: Update, context: CallbackContext) -> None:
    request = " ".join(context.args)
    response = send_request(request)
    update.message.reply_text(response)

def get_log(update: Update, context: CallbackContext) -> None:
    response = send_request('getfile', update, context)
    update.message.reply_text(response)

def shutdown(update: Update, context: CallbackContext) -> None:
    response = send_request('shutdown', update, context)
    update.message.reply_text(response)

def add_computer(update: Update, context: CallbackContext) -> None:
    random_string = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(128))
    update.message.reply_text("Сгенерировано случайное значение для добавления компьютера: " + random_string)
    
   # def wait_for_response(msg):
    #    if msg.text == random_string:
         #   wait_for_string_and_return_ip(random_string)
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS Computers
                (ip TEXT, id TEXT, token TEXT, info TEXT)''')
    add_computer_to_db(conn, wait_for_string_and_return_ip(random_string), str(update.message.from_user.id), random_string, '-')
    update.message.reply_text("Информация о компьютере добавлена в базу данных")

    update.message.reply_text()
    conn.close()

def get_tokens_by_user_id(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    # Выполняем запрос к базе данных для извлечения токенов пользователя
    cursor.execute("SELECT token FROM Computers WHERE id=?", (user_id,))
    tokens = cursor.fetchall()

    conn.close()

    return [token[0] for token in tokens] if tokens else []


# Функция для получения токенов по ID пользователя из базы данных
def get_tokens_by_user_id(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    # Выполняем запрос к базе данных для извлечения токенов пользователя
    cursor.execute("SELECT token FROM Computers WHERE id=?", (user_id,))
    tokens = cursor.fetchall()

    conn.close()

    return [token[0] for token in tokens] if tokens else []

# Функция для обработки команды /computers
def computers(update: Update, context: CallbackContext) -> None:
    user_id = update.message.from_user.id
    tokens = get_tokens_by_user_id(user_id)
    if tokens:
        update.message.reply_text(f'Твои токены: {", ".join(tokens)}')
    else:
        update.message.reply_text('У тебя пока нет ни одного токена')

# Функция для обработки команды /changecomp
def change_comp(update: Update, context: CallbackContext) -> None:
    user_id = update.message.from_user.id
    tokens = get_tokens_by_user_id(user_id)
    if tokens:
        comp_keyboard = [[str(token)] for token in tokens]
        reply_markup = ReplyKeyboardMarkup(comp_keyboard, one_time_keyboard=True)
        update.message.reply_text("Выберите компьютер:", reply_markup=reply_markup)
        # Сохраняем выбранный компьютер для дальнейшего использования
        context.user_data['selected_comp'] = None  # Начинаем с None
    else:
        update.message.reply_text('У тебя пока нет ни одного токена')

# Обработчик сообщений с выбранным компьютером
def handle_selected_comp(update: Update, context: CallbackContext) -> None:
    selected_comp = update.message.text
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    # Выполняем запрос к базе данных для извлечения токенов пользователя
    cursor.execute("SELECT ip FROM Computers WHERE token='" + str(selected_comp) + "'")
    ip = cursor.fetchall()
 
    conn.close()
    print(ip)
    context.user_data['selected_comp'] = ip[0][0]
    update.message.reply_text(f'Выбран компьютер с IP: {context.user_data['selected_comp']}')
        

def help_command(update: Update, context):
    help_text = "Список доступных команд:\n"
    help_text += "/start - Начать диалог\n"
    help_text += "/help - Получить справку о доступных командах\n"
    help_text += "/changecomp - Выбрать компьютер\n"
    help_text += "/addcomputer - Добавить компьютер\n"
    help_text += "/computers - Посмотреть компьютеры\n"
    help_text += "/getlog - Получить лог с компьютера\n"
    help_text += "/shutdown - Выключить компьютер\n"

    update.message.reply_text(help_text)

def main() -> None:
    updater = Updater("7208856903:AAFdn45QRYnsA5lGn5gnIbr_gPN5hrswG-c")

    updater.dispatcher.add_handler(CommandHandler("send_request", send_request_command))
    updater.dispatcher.add_handler(CommandHandler("getlog", get_log))
    updater.dispatcher.add_handler(CommandHandler("shutdown", shutdown))
    updater.dispatcher.add_handler(CommandHandler("addcomputer", add_computer))
    updater.dispatcher.add_handler(CommandHandler("computers", computers))
    updater.dispatcher.add_handler(CommandHandler("changecomp", change_comp))
    updater.dispatcher.add_handler(CommandHandler("help", help_command))
    updater.dispatcher.add_handler(CommandHandler("start", help_command))
    updater.dispatcher.add_handler(MessageHandler(Filters.text & (~Filters.command), handle_selected_comp))
    updater.start_polling()
    updater.idle()

if __name__ == '__main__':
    main()