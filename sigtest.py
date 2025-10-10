import signal
import readline

PROMPT = 'minishell$ '

running = True

def handler(signum, frame):
    global running
    print('\nhandler called signal', signum)
    running = False

signal.signal(signal.SIGINT, handler)

while running:
    try:
        line = input(PROMPT)
    except EOFError:
        break
    running = False
