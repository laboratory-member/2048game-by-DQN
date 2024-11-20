from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time

# 启动Chrome浏览器
driver = webdriver.Chrome()  # 不需要指定路径

try:
    # 打开网页
    driver.get("https://2048game.com/")

    # 等待页面加载完成
    time.sleep(2)

    for _ in range(1000):

        # 模拟按下 "向下箭头" 键
        driver.find_element(By.TAG_NAME, 'body').send_keys(Keys.DOWN)
        time.sleep(0.05)

        # 模拟按下 "向左箭头" 键
        driver.find_element(By.TAG_NAME, 'body').send_keys(Keys.LEFT)
        time.sleep(0.05)

finally:
    # 关闭浏览器
    driver.quit()