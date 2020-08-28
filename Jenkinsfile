
pipeline {
	agent { label 'CI-W10-Slave'}
	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
	parameters {
	    booleanParam name: 'RUN_TESTS', defaultValue: true, description: 'Run Tests?'
	    booleanParam name: 'ARCHIVE', defaultValue: true, description: 'Archive artifacts?'
	}
	stages {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'MSYS', generator: "CodeBlocks - MinGW Makefiles", steps: [[withCmake: true, envVars: 'DESTDIR=${WORKSPACE}/artifacts']]
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Test') {
            when {
                environment name: 'RUN_TESTS', value: 'true'
            }
            steps {
                ctest 'InSearchPath'
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Archive') {
            when {
                environment name: 'ARCHIVE', value: 'true'
            }
            steps {
                archiveArtifacts artifacts: 'artifacts\\*'
                cleanWs()
            }
            post {
                always {
                    cleanWs()
                }
            }
        }
	}
}