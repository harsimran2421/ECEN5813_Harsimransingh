import datetime
import time
import calendar
import os
import logging

logger = logging.getLogger('logfile')
hdlr = logging.FileHandler('C:/Users/modak/Documents/DS-5 Workspace/Logger/logfile.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr) 
logger.setLevel(logging.INFO)

fh = open('teraterm_final.txt')
for line in fh:
    if "Timestamp:" in line:
        line1 = line.split(":")[1]
        line2 = line1.split()
        #day = line2[0]
        #print(day)
        month = line2[1]
        if month == "Jan":
            month = "01"
        if month == "Feb":
            month = "02"
        if month == "Mar":
            month = "03"
        if month == "Apr":
            month = "04"
        if month == "May":
            month = "05"
        if month == "Jun":
            month = "06"
        if month == "Jul":
            month = "07"
        if month == "Aug":
            month = "08"
        if month == "Sep":
            month = "09"
        if month == "Oct":
            month = "10"
        if month == "Nov":
            month = "11"
        if month == "Dec":
            month = "12"
        #print(month)        
        day = line2[2]
        #print(day) 
        line3 = line.split()
        year = line3[4]  
        #print(year)
        hours = line2[3]
        #print(hours)
        mins = line.split(":")[2]
        #print("mins " +mins)
        secs = line.split(":")[3].split()[0]
        #print("secs " + secs)
        #print(datetime.datetime(int(year),int(month),int(day),int(hours),int(mins)).timestamp())
        time_a  = datetime.datetime(int(year),int(month),int(day),int(hours),int(mins),int(secs))
        epoch = calendar.timegm(time_a.timetuple())
        #print("Epoch " + str(epoch))
        ctm = os.path.getctime('teraterm1.txt')
        #print(ctm)
        newtm = epoch + ctm
        #print(newtm)
        functime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(newtm))
        
        ID = line.split(":")[4].split()[0]
        #print(ID)
        if ID == "1":
            logger.info(functime + " RTC_INITIALIZED")
        if ID == "2":
            logger.info(functime + " LOGGER_INITIALIZED")
        if ID == "3":
            logger.info(functime + " GPIO_INITIALIZED")
        if ID == "4":
            logger.info(functime + " SPI_INITIALIZED")
        if ID == "5":
            logger.info(functime + " SYSTEM_INITIALIZED")
        if ID == "6":
            logger.info(functime + " SYSTEM_HALTED")
        if ID == "7":
            logger.info(functime + " INFO")
        if ID == "8":
            logger.info(functime + " WARNING")
        if ID == "9":
            logger.info(functime + " LOG_ERROR")
        if ID == "10":
            logger.info(functime + " DATA_RECEIVED")
        if ID == "11":
            logger.info(functime + " DATA_ANALYSIS_STARTED")
        if ID == "12":
            logger.info(functime + " DATA_ALPHA_COUNT")
        if ID == "13":
            logger.info(functime + " NUMERIC_COUNT")
        if ID == "14":
            logger.info(functime + " DATA_PUNCTUATION_COUNT")
        if ID == "15":
            logger.info(functime + " DATA_MISC_COUNT")
        if ID == "16":
            logger.info(functime + " DATA_ANALYSIS_COMPLETED")
        if ID == "17":
            logger.info(functime + " HEARTBEAT")
        
print("End")