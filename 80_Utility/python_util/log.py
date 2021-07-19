import logging
logging.basicConfig(
    filename='testLog.txt', level=logging.DEBUG,
    format=' %(asctime)s - %(levelname)s - %(message)s ')

# logging.disable(logging.CRITICAL)
logging.debug('start')
# main()
logging.debug('end')
