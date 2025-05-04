from classes.banco import Banco

class Especie(): # está é o nome da classe de Espécies
    '''
        Documentação da classe
        - aqui nó vamos descrever os campos (propriedades) e funções (métodos) para definirmos de acordo com a teoria de Programação Orientada a Objetos
    '''
    # Construtor
    def __init__(self):
        # propriedades privadas
        self.__id = 0
        self.__descricao = ''
        self.__origem = ''
        self.__banco = Banco() # aqui será criado o objeto que representa o acesso ao Banco de Dados, nós iremos utilizar ela para gravar, excluir, alterar e buscar os dados já gravados no banco
        # propriedades públicas

    # definir os métodos para a nossa classe para colocar os valores nas propriedades
    def set_id(self, pId): # setar o valor é autoincremento
        if pId > 0: # validação dos valores para não serem negativos ou zerados, e serem corretamente associados à propriedade
            self.__id = pId
    def set_descricao(self,pDescr):
        if len(pDescr) > 0:
            self.__descricao = pDescr

    def set_origem(self,pOrigem):
        self.__origem = pOrigem

    # métodos para obter os valores das propriedades
    def get_id(self):
        return self.__id

    def get_descricao(self):
        return self.__descricao

    def get_origem(self):
        return self.__origem

    # devolver todas as espécies cadastradas no banco de dados na tabela Especies
    def obterEspecies(self):
        sql = '''
              SELECT esp_id, esp_descricao,esp_origem
              FROM Especies
              ORDER by esp_descricao
              '''
        return self.__banco.executarSelect(sql)

    def gravar(self): # vai pegar os dados do objeto e gravar na tabela do banco
        sql = ''' INSERT INTO Especies (esp_descricao,esp_origem)
                 values ("#descr", "#origem")
              '''
        sql = sql.replace('#descr',self.__descricao)
        sql = sql.replace('#origem', self.__origem)
        return self.__banco.executarInsertUpdateDelete(sql)

    # devolver uma espécia só cdastrada no banco de dados na tabela Especies
    def obterEspecie(self, pId=0):
        if pId != 0:
            self.__id = pId
        sql = ''' SELECT esp_id, esp_descricao,esp_origem
                  FROM Especies
                  where esp_id = #id         '''
        sql = sql.replace('#id', str(self.__id))
        return self.__banco.executarSelect(sql)

    def excluir(self):
        sql = 'delete from Especies where esp_id = #id'
        sql = sql.replace('#id', str(self.__id))
        return self.__banco.executarInsertUpdateDelete(sql)

    def alterar(self):
        sql = 'update Especies set esp_descricao = "#descr", esp_origem = "#origem" where esp_id = #id'
        sql = sql.replace('#descr',self.__descricao)
        sql = sql.replace('#origem',self.__origem)
        sql = sql.replace('#id',str(self.__id))
        return self.__banco.executarInsertUpdateDelete(sql)
